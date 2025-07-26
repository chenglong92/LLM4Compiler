// original code(id = 75): 
 /*
__global__ void mult_add_into_kernel ( int n , float * a , float * b , float * c ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < n ) { c [ i ] += a [ i ] * b [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void mult_add_into_kernel(int n, float* a, float* b, float* c) {
    for (int i = 0; i < n; ++i) {
        c[i] += a[i] * b[i];
    }
}

int main() {
    // Test case 1: Basic test with positive numbers
    {
        int n = 3;
        float a[] = {1.0f, 2.0f, 3.0f};
        float b[] = {4.0f, 5.0f, 6.0f};
        float c[] = {0.0f, 0.0f, 0.0f};
        float expected[] = {4.0f, 10.0f, 18.0f};
        
        mult_add_into_kernel(n, a, b, c);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Test with negative numbers
    {
        int n = 4;
        float a[] = {-1.0f, -2.0f, 3.0f, -4.0f};
        float b[] = {5.0f, -6.0f, -7.0f, 8.0f};
        float c[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float expected[] = {-4.0f, 14.0f, -18.0f, -28.0f};
        
        mult_add_into_kernel(n, a, b, c);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 3: Test with zero values
    {
        int n = 3;
        float a[] = {0.0f, 0.0f, 0.0f};
        float b[] = {1.0f, 2.0f, 3.0f};
        float c[] = {10.0f, 20.0f, 30.0f};
        float expected[] = {10.0f, 20.0f, 30.0f};
        
        mult_add_into_kernel(n, a, b, c);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Test with single element
    {
        int n = 1;
        float a[] = {2.5f};
        float b[] = {4.0f};
        float c[] = {1.0f};
        float expected[] = {11.0f};
        
        mult_add_into_kernel(n, a, b, c);
        
        assert(c[0] == expected[0]);
    }

    // Test case 5: Test with large array
    {
        const int n = 1000;
        float a[n], b[n], c[n], expected[n];
        
        for (int i = 0; i < n; ++i) {
            a[i] = i * 1.0f;
            b[i] = i * 2.0f;
            c[i] = i * 3.0f;
            expected[i] = c[i] + a[i] * b[i];
        }
        
        mult_add_into_kernel(n, a, b, c);
        
        for (int i = 0; i < n; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 6: Test with n = 0 (empty arrays)
    {
        int n = 0;
        float* a = nullptr;
        float* b = nullptr;
        float* c = nullptr;
        
        mult_add_into_kernel(n, a, b, c);
        // No assertion needed as function should handle n=0 gracefully
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}