// original code(id = 34): 
 /*
__global__ void operacionKernelGPU ( float * u , float * lu , float u_m , float u_d , int n ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx < n ) lu [ idx ] = ( u [ idx ] - u_m ) / u_d ; }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void operacionCPU(float* u, float* lu, float u_m, float u_d, int n) {
    for (int idx = 0; idx < n; ++idx) {
        lu[idx] = (u[idx] - u_m) / u_d;
    }
}

void test_operacionCPU() {
    // Test case 1: Basic test with positive values
    {
        float u[] = {10.0f, 20.0f, 30.0f};
        float lu[3];
        float u_m = 15.0f;
        float u_d = 5.0f;
        int n = 3;
        
        operacionCPU(u, lu, u_m, u_d, n);
        
        assert(fabs(lu[0] - (-1.0f)) < 1e-6);
        assert(fabs(lu[1] - 1.0f) < 1e-6);
        assert(fabs(lu[2] - 3.0f) < 1e-6);
    }
    
    // Test case 2: Test with negative values
    {
        float u[] = {-5.0f, 0.0f, 5.0f};
        float lu[3];
        float u_m = 0.0f;
        float u_d = 5.0f;
        int n = 3;
        
        operacionCPU(u, lu, u_m, u_d, n);
        
        assert(fabs(lu[0] - (-1.0f)) < 1e-6);
        assert(fabs(lu[1] - 0.0f) < 1e-6);
        assert(fabs(lu[2] - 1.0f) < 1e-6);
    }
    
    // Test case 3: Test with zero division (should handle infinity or NaN)
    {
        float u[] = {1.0f, 2.0f, 3.0f};
        float lu[3];
        float u_m = 0.0f;
        float u_d = 0.0f;
        int n = 3;
        
        operacionCPU(u, lu, u_m, u_d, n);
        
        // Check for infinity or NaN (implementation dependent)
        assert(std::isinf(lu[0]) || std::isnan(lu[0]));
        assert(std::isinf(lu[1]) || std::isnan(lu[1]));
        assert(std::isinf(lu[2]) || std::isnan(lu[2]));
    }
    
    // Test case 4: Test with single element
    {
        float u[] = {100.0f};
        float lu[1];
        float u_m = 50.0f;
        float u_d = 25.0f;
        int n = 1;
        
        operacionCPU(u, lu, u_m, u_d, n);
        
        assert(fabs(lu[0] - 2.0f) < 1e-6);
    }
    
    // Test case 5: Test with large array
    {
        const int n = 1000;
        float u[n];
        float lu[n];
        float u_m = 500.0f;
        float u_d = 100.0f;
        
        for (int i = 0; i < n; ++i) {
            u[i] = static_cast<float>(i);
        }
        
        operacionCPU(u, lu, u_m, u_d, n);
        
        for (int i = 0; i < n; ++i) {
            float expected = (static_cast<float>(i) - u_m) / u_d;
            assert(fabs(lu[i] - expected) < 1e-6);
        }
    }
}

int main() {
    test_operacionCPU();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}