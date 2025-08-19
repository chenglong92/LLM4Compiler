import torch
import triton
import triton.language as tl

def get_autotune_config():
    return [
        triton.Config({"BLOCK_SIZE": 16}),
        triton.Config({"BLOCK_SIZE": 32}),
    ]


@triton.autotune(
    configs=get_autotune_config(),
    key=["m", "n", "k"],
)
@triton.jit
def gemm_kernel_1D(A_ptr,
                   B_ptr,
                   C_ptr,
                   m,
                   n,
                   k,
                   stride_Am,
                   stride_Bn,
                   BLOCK_SIZE: tl.constexpr):
    # get the pid number.
    pid = tl.program_id(axis=0)
    #
    block_start_Ax = pid * BLOCK_SIZE
    offsets_block = tl.arange(0, BLOCK_SIZE)
    for n0 in range(0, tl.cdiv(n, BLOCK_SIZE)):
        block_start_By = n0 * BLOCK_SIZE
        C = tl.zeros((BLOCK_SIZE, BLOCK_SIZE), dtype = tl.float32)
        for k0 in range(0, tl.cdiv(k, BLOCK_SIZE)):
            block_start_A = block_start_Ax * stride_Am + k0 * BLOCK_SIZE
            block_start_B = k0 * BLOCK_SIZE * stride_Bn + block_start_By
            offsets_A = block_start_A + offsets_block[:, None] * stride_Am + offsets_block[None, :]
            offsets_B = block_start_B + offsets_block[:, None] * stride_Bn + offsets_block[None, :]
            A = tl.load(A_ptr + offsets_A)
            B = tl.load(B_ptr + offsets_B)
            C = tl.dot(A, B, C)
        block_start_C = block_start_Ax * stride_Bn + block_start_By 
        offsets_C = block_start_C + offsets_block[:, None] * stride_Bn + offsets_block[None, :]
        tl.store(C_ptr + offsets_C, C)

@triton.jit
def gemm_kernel_2d(A_ptr,
                   B_ptr,
                   C_ptr,
                   M,
                   N,
                   K,
                   BLOCK_SIZE_M: tl.constexpr,
                   BLOCK_SIZE_N: tl.constexpr,
                   BLOCK_SIZE_K: tl.constexpr):
    pid = tl.program_id(axis = 0)
    num_pid0 = tl.cdiv(M, BLOCK_SIZE_M)
    num_pid1 = tl.cdiv(N, BLOCK_SIZE_N)
    pid0 = pid // num_pid1
    pid1 = pid % num_pid1
    #
    start_A = pid0 * BLOCK_SIZE_M
    offsets_block_M = tl.arange(0, BLOCK_SIZE_M)
    offsets_block_N = tl.arange(0, BLOCK_SIZE_N)
    offsets_block_K = tl.arange(0, BLOCK_SIZE_K)
    C = tl.zeros((BLOCK_SIZE_M, BLOCK_SIZE_N), dtype = tl.float32)
    for k0 in range(0, tl.cdiv(K, BLOCK_SIZE_K)):
        start_block_A = start_A * K + k0 * BLOCK_SIZE_K
        start_block_B = k0 * BLOCK_SIZE_K * N + pid1 * BLOCK_SIZE_N
        offsets_block_A = start_block_A + offsets_block_M[:, None] * K + offsets_block_K[None, :]
        offsets_block_B = start_block_B + offsets_block_K[:, None] * N + offsets_block_N[None, :]
        A = tl.load(A_ptr + offsets_block_A)
        B = tl.load(B_ptr + offsets_block_B)
        C = tl.dot(A, B, C)
    start_block_C = start_A * N + pid1 * BLOCK_SIZE_N
    offsets_block_C = start_block_C + offsets_block_M[:, None] * N + offsets_block_N[None, :]
    tl.store(C_ptr + offsets_block_C, C)

def gemm_1D(A: torch.Tensor, B: torch.Tensor, M: int, N: int, K: int):
    BLOCK_SIZE = 16
    C = torch.zeros((M, N), device=A.device, dtype=torch.float32)
    grid = lambda meta: (triton.cdiv(M, meta['BLOCK_SIZE']),)
    #gemm_kernel_1D[grid](A, B, C, M, N, K, stride_Am = K, stride_Bn = N, BLOCK_SIZE=BLOCK_SIZE)
    gemm_kernel_1D[grid](A, B, C, M, N, K, stride_Am = K, stride_Bn = N)
    return C

def gemm_2D(A: torch.Tensor, B: torch.Tensor, M: int, N: int, K: int):
    BLOCK_SIZE_M = 16
    BLOCK_SIZE_N = 16
    BLOCK_SIZE_K = 16
    C = torch.zeros((M, N), device = A.device, dtype = torch.float32)
    grid = lambda meta: (triton.cdiv(M, meta['BLOCK_SIZE_M']) * triton.cdiv(N, meta['BLOCK_SIZE_N']), )
    gemm_kernel_2d[grid](A, B, C, M, N, K, BLOCK_SIZE_M = BLOCK_SIZE_M, BLOCK_SIZE_N = BLOCK_SIZE_N, BLOCK_SIZE_K = BLOCK_SIZE_K)
    return C

LINE_VALS = [
    'triton-cpu', 'torch-cpu'
]
LINE_NAMES = [
    'TritonCPU', 'TorchCPU'
]
LINE_STYLES = [('blue', '--'), ('green', '-')]


@triton.testing.perf_report(
    triton.testing.Benchmark(
        x_names=['size'],  # Argument names to use as an x-axis for the plot.
        x_vals=[2**i for i in range(7, 10, 1)],  # Different possible values for `x_name`.
        x_log=True,  # x axis is logarithmic.
        line_arg='provider',  # Argument name whose value corresponds to a different line in the plot.
        line_vals=LINE_VALS,  # Possible values for `line_arg`.
        line_names=LINE_NAMES,  # Label name for the lines.
        styles=LINE_STYLES,  # Line styles.
        ylabel='GB/s',  # Label name for the y-axis.
        plot_name=
        # Name for the plot. Used also as a file name for saving the plot.
        'matmul-performance',
        args={},  # Values for function arguments not in `x_names` and `y_name`.
    ))
def benchmark(size, provider):
    torch.manual_seed(0)
    M = size
    N = size
    K = size
    device = 'cpu'
    A = torch.randn((M, K), device = device, dtype = torch.float32)
    B = torch.randn((K, N), device = device, dtype = torch.float32)

    triton.runtime.driver.set_active_to_cpu()

    quantiles = [0.5, 0.2, 0.8]
    if provider == 'torch-cpu':
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: torch.matmul(A, B), quantiles=quantiles)
    elif provider == 'triton-cpu':
        ms, min_ms, max_ms = triton.testing.do_bench(lambda: gemm_1D(A, B, M, N, K), quantiles=quantiles)
    gbps = lambda ms: 2 * M * N * K * 1e-9 / (ms * 1e-3)
    return gbps(ms), gbps(max_ms), gbps(min_ms)


if __name__ == "__main__":
    #'''
    torch.manual_seed(0)
    M = 32
    N = 32
    K = 32
    device = 'cpu'
    A = torch.randn((M, K), device = device, dtype = torch.float32)
    B = torch.randn((K, N), device = device, dtype = torch.float32)
    #
    C_golden = torch.matmul(A, B)
    #
    C = gemm_1D(A, B, M, N, K)
    #
    C_2D = gemm_2D(A, B, M, N, K)
    #
    print(f"C_golden - C: {C_golden - C}")
    print(f"err: {torch.allclose(C, C_golden, atol = 1e-5)}")
    print(f"C_golden - C_2D: {C_golden - C_2D}")
    print(f"err: {torch.allclose(C_2D, C_golden, atol = 1e-5)}")
    #'''
    #benchmark.run(print_data=True, show_plots=True)


