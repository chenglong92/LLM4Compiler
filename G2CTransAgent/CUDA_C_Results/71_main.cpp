// original code(id = 71): 
 /*
__global__ void kComputeActs ( const float * d_nets , float * d_acts ) { int un_idx = blockIdx . x * blockDim . x + threadIdx . x ; float tact = 1.0f / ( 1.0f + expf ( - d_acts [ un_idx ] ) ) ; __syncthreads ( ) ; d_acts [ un_idx ] = tact ; }
*/
// optimized code: 

#include <cmath>
#include <iostream>
#include <cassert>
#include <limits>

void kComputeActs(const float* d_nets, float* d_acts, int size) {
    for (int un_idx = 0; un_idx < size; ++un_idx) {
        float tact = 1.0f / (1.0f + expf(-d_acts[un_idx]));
        d_acts[un_idx] = tact;
    }
}

void test_normal_case() {
    const int size = 5;
    float d_nets[size] = {0};  // unused
    float d_acts[size] = {-2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    float expected[size] = {
        1.0f / (1.0f + expf(2.0f)),
        1.0f / (1.0f + expf(1.0f)),
        1.0f / (1.0f + expf(0.0f)),
        1.0f / (1.0f + expf(-1.0f)),
        1.0f / (1.0f + expf(-2.0f))
    };
    
    kComputeActs(d_nets, d_acts, size);
    
    for (int i = 0; i < size; ++i) {
        assert(fabs(d_acts[i] - expected[i]) < 1e-6f);
    }
    std::cout << "Normal case test passed.\n";
}

void test_boundary_case() {
    const int size = 4;
    float d_nets[size] = {0};
    float d_acts[size] = {
        -std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(),
        0.0f,
        std::numeric_limits<float>::min()
    };
    
    kComputeActs(d_nets, d_acts, size);
    
    assert(d_acts[0] < 1e-40f);  // Should be very close to 0
    assert(fabs(d_acts[1] - 1.0f) < 1e-6f);  // Should be very close to 1
    assert(fabs(d_acts[2] - 0.5f) < 1e-6f);  // Exactly 0.5
    assert(d_acts[3] > 0.5f);  // Very small positive should be > 0.5
    
    std::cout << "Boundary case test passed.\n";
}

void test_zero_size() {
    float d_nets[1] = {0};
    float d_acts[1] = {1.0f};
    
    kComputeActs(d_nets, d_acts, 0);
    
    // Should not crash or modify d_acts
    assert(d_acts[0] == 1.0f);
    std::cout << "Zero size test passed.\n";
}

void test_null_pointers() {
    // Test with null d_acts (shouldn't crash, though behavior is technically undefined)
    float dummy = 1.0f;
    kComputeActs(&dummy, nullptr, 1);
    
    // Test with null d_nets (should work fine since d_nets isn't used)
    float d_acts[1] = {0.0f};
    kComputeActs(nullptr, d_acts, 1);
    
    std::cout << "Null pointers test passed (no crash).\n";
}

int main() {
    test_normal_case();
    test_boundary_case();
    test_zero_size();
    test_null_pointers();
    
    std::cout << "All tests passed successfully.\n";
    return 0;
}