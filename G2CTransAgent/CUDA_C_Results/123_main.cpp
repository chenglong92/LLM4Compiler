// original code(id = 123): 
 /*
__global__ void saxpy_gpu_kernel ( float * x , float * y , float alpha , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { y [ i ] = alpha * x [ i ] + y [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <vector>

void saxpy_cpu(float* x, float* y, float alpha, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = alpha * x[i] + y[i];
    }
}

void test_saxpy_cpu() {
    // Test case 1: Basic test with positive values
    {
        float x[] = {1.0f, 2.0f, 3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float alpha = 2.0f;
        int n = 3;
        float expected[] = {6.0f, 9.0f, 12.0f};
        
        saxpy_cpu(x, y, alpha, n);
        
        for (int i = 0; i < n; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 2: Test with negative values
    {
        float x[] = {-1.0f, -2.0f, -3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float alpha = -1.0f;
        int n = 3;
        float expected[] = {5.0f, 7.0f, 9.0f};
        
        saxpy_cpu(x, y, alpha, n);
        
        for (int i = 0; i < n; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 3: Test with zero alpha
    {
        float x[] = {1.0f, 2.0f, 3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float alpha = 0.0f;
        int n = 3;
        float expected[] = {4.0f, 5.0f, 6.0f};
        
        saxpy_cpu(x, y, alpha, n);
        
        for (int i = 0; i < n; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 4: Test with single element
    {
        float x[] = {5.0f};
        float y[] = {10.0f};
        float alpha = 0.5f;
        int n = 1;
        float expected[] = {12.5f};
        
        saxpy_cpu(x, y, alpha, n);
        
        assert(y[0] == expected[0]);
    }

    // Test case 5: Test with empty array (should do nothing)
    {
        float x[] = {};
        float y[] = {};
        float alpha = 1.0f;
        int n = 0;
        
        saxpy_cpu(x, y, alpha, n);
        // No assertion needed as it should just not crash
    }

    // Test case 6: Test with large array
    {
        const int n = 1000;
        std::vector<float> x(n, 2.0f);
        std::vector<float> y(n, 3.0f);
        float alpha = 1.5f;
        std::vector<float> expected(n, 6.0f);
        
        saxpy_cpu(x.data(), y.data(), alpha, n);
        
        for (int i = 0; i < n; ++i) {
            assert(y[i] == expected[i]);
        }
    }
}

int main() {
    test_saxpy_cpu();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}