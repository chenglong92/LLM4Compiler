// original code(id = 49): 
 /*
__global__ void saxpy_gpu ( const int dim , float a , float * x , float * y ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < dim ) y [ i ] = a * x [ i ] + y [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void saxpy_cpu(const int dim, float a, float* x, float* y) {
    for (int i = 0; i < dim; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

void test_saxpy_basic() {
    const int dim = 3;
    float a = 2.0f;
    float x[dim] = {1.0f, 2.0f, 3.0f};
    float y[dim] = {4.0f, 5.0f, 6.0f};
    float expected[dim] = {6.0f, 9.0f, 12.0f};
    
    saxpy_cpu(dim, a, x, y);
    
    for (int i = 0; i < dim; ++i) {
        assert(fabs(y[i] - expected[i]) < 1e-6);
    }
}

void test_saxpy_zero_dim() {
    const int dim = 0;
    float a = 2.0f;
    float x[1] = {1.0f};  // dummy
    float y[1] = {2.0f};  // dummy
    
    saxpy_cpu(dim, a, x, y);
    // Should do nothing, just verify no crash
}

void test_saxpy_zero_a() {
    const int dim = 3;
    float a = 0.0f;
    float x[dim] = {1.0f, 2.0f, 3.0f};
    float y[dim] = {4.0f, 5.0f, 6.0f};
    float expected[dim] = {4.0f, 5.0f, 6.0f};
    
    saxpy_cpu(dim, a, x, y);
    
    for (int i = 0; i < dim; ++i) {
        assert(fabs(y[i] - expected[i]) < 1e-6);
    }
}

void test_saxpy_negative_a() {
    const int dim = 3;
    float a = -1.5f;
    float x[dim] = {2.0f, -4.0f, 6.0f};
    float y[dim] = {1.0f, 2.0f, 3.0f};
    float expected[dim] = {-2.0f, 8.0f, -6.0f};
    
    saxpy_cpu(dim, a, x, y);
    
    for (int i = 0; i < dim; ++i) {
        assert(fabs(y[i] - expected[i]) < 1e-6);
    }
}

void test_saxpy_large_dim() {
    const int dim = 1000;
    float a = 0.5f;
    float x[dim];
    float y[dim];
    float expected[dim];
    
    for (int i = 0; i < dim; ++i) {
        x[i] = static_cast<float>(i);
        y[i] = static_cast<float>(dim - i);
        expected[i] = a * x[i] + y[i];
    }
    
    saxpy_cpu(dim, a, x, y);
    
    for (int i = 0; i < dim; ++i) {
        assert(fabs(y[i] - expected[i]) < 1e-6);
    }
}

void test_saxpy_mixed_values() {
    const int dim = 5;
    float a = 1.5f;
    float x[dim] = {0.0f, -1.0f, 2.5f, -3.0f, 4.0f};
    float y[dim] = {2.0f, 0.0f, -1.0f, 3.0f, -2.0f};
    float expected[dim] = {2.0f, -1.5f, 2.75f, -1.5f, 4.0f};
    
    saxpy_cpu(dim, a, x, y);
    
    for (int i = 0; i < dim; ++i) {
        assert(fabs(y[i] - expected[i]) < 1e-6);
    }
}

int main() {
    test_saxpy_basic();
    test_saxpy_zero_dim();
    test_saxpy_zero_a();
    test_saxpy_negative_a();
    test_saxpy_large_dim();
    test_saxpy_mixed_values();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}