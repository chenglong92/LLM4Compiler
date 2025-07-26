// original code(id = 163): 
 /*
__global__ void gpu_add ( float * c , float * a , float * b , int n ) { for ( int k = threadIdx . x ; k < n ; k += blockDim . x ) { c [ k ] = a [ k ] + b [ k ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void cpu_add(float* c, float* a, float* b, int n) {
    for (int k = 0; k < n; ++k) {
        c[k] = a[k] + b[k];
    }
}

int main() {
    // Test case 1: Normal case with small array
    {
        const int n = 5;
        float a[n] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float b[n] = {0.5f, 1.5f, 2.5f, 3.5f, 4.5f};
        float c[n];
        float expected[n] = {1.5f, 3.5f, 5.5f, 7.5f, 9.5f};
        
        cpu_add(c, a, b, n);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Edge case with empty array
    {
        const int n = 0;
        float* a = nullptr;
        float* b = nullptr;
        float* c = nullptr;
        
        cpu_add(c, a, b, n); // Should handle empty array without crashing
    }

    // Test case 3: Normal case with larger array
    {
        const int n = 100;
        float a[n], b[n], c[n];
        float expected[n];
        
        for (int i = 0; i < n; ++i) {
            a[i] = static_cast<float>(i);
            b[i] = static_cast<float>(2 * i);
            expected[i] = a[i] + b[i];
        }
        
        cpu_add(c, a, b, n);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Edge case with single element
    {
        const int n = 1;
        float a[n] = {3.14f};
        float b[n] = {2.71f};
        float c[n];
        float expected[n] = {5.85f};
        
        cpu_add(c, a, b, n);
        
        assert(c[0] == expected[0]);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}