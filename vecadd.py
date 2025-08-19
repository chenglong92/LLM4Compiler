import torch
import triton
import triton.language as tl

CPU_BLOCK_SIZE = 128

@triton.jit
def add_kernel(x_ptr,  # *Pointer* to first input vector.
               y_ptr,  # *Pointer* to second input vector.
               output_ptr,  # *Pointer* to output vector.
               n_elements,  # Size of the vector.
               BLOCK_SIZE: tl.constexpr,  # Number of elements each program should process.
               # NOTE: `constexpr` so it can be used as a shape value.
               ):
    # There are multiple 'programs' processing different data. We identify which program
    # we are here:
    pid = tl.program_id(axis=0)  # We use a 1D launch grid so axis is 0.
    # This program will process inputs that are offset from the initial data.
    # For instance, if you had a vector of length 256 and block_size of 64, the programs
    # would each access the elements [0:64, 64:128, 128:192, 192:256].
    # Note that offsets is a list of pointers:
    block_start = pid * BLOCK_SIZE
    offsets = block_start + tl.arange(0, BLOCK_SIZE)
    # Create a mask to guard memory operations against out-of-bounds accesses.
    mask = offsets < n_elements
    # Load x and y from DRAM, masking out any extra elements in case the input is not a
    # multiple of the block size.
    x = tl.load(x_ptr + offsets, mask=mask)
    y = tl.load(y_ptr + offsets, mask=mask)
    output = x + y
    # Write x + y back to DRAM.
    tl.store(output_ptr + offsets, output, mask=mask)


@triton.jit
def vecadd_kernel_tile(A_ptr,
                  B_ptr,
                  output_ptr,
                  n,
                  BLOCK_SIZE: tl.constexpr,
                  TILE_SIZE: tl.constexpr,):
    pid = tl.program_id(axis = 0)
    block_start = pid * BLOCK_SIZE
    for i in range(0, tl.cdiv(BLOCK_SIZE, TILE_SIZE)):
        offsets = block_start + i * TILE_SIZE + tl.arange(0, TILE_SIZE)
        mask = offsets < n
        A_block_ptr = tl.load(A_ptr + offsets, mask = mask)
        B_block_ptr = tl.load(B_ptr + offsets, mask = mask)
        C = A_block_ptr + B_block_ptr
        tl.store(output_ptr + offsets, C, mask = mask)

def vecadd(A: torch.Tensor, B: torch.Tensor, C):
    BLOCK_SIZE = 64
    TILE_SIZE = 16
    if C is None:
        C = torch.empty_like(A)
    n = A.numel()
    grid = lambda meta: (triton.cdiv(n, meta['BLOCK_SIZE']), )
    vecadd_kernel[grid](A, B, C, n, BLOCK_SIZE=64)
    #print(C)
    return C

def add_tiled(x: torch.Tensor, y: torch.Tensor, output):
    if output is None:
        output = torch.empty_like(x)
    n_elements = output.numel()
    grid = lambda meta: (triton.cdiv(n_elements, meta['BLOCK_SIZE']), )
    add_kernel[grid](x, y, output, n_elements, BLOCK_SIZE=CPU_BLOCK_SIZE)
    return output

if __name__ == "__main__":
    DEVICE = triton.runtime.driver.active.get_active_torch_device().type
    n = 1024
    torch.manual_seed(0)
    triton.runtime.driver.set_active_to_cpu()
    A = torch.rand(n, device = DEVICE)
    B = torch.rand(n, device = DEVICE)
    #C = vecadd(A, B, None)
    C = add_tiled(A, B, None)
    C1 = A + B
    print(C1)
    print(C)

