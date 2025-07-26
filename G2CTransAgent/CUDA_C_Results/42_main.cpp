// original code(id = 42): 
 /*
__global__ void add_arrays ( int n , float * x , float * y , float * z ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i < n ) { z [ i ] = x [ i ] + y [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void add_arrays(int n, float* x, float* y, float* z) {
    for (int i = 0; i < n; ++i) {
        z[i] = x[i] + y[i];
    }
}

int main() {
    // Test case 1: Basic addition with positive numbers
    {
        int n = 3;
        float x[] = {1.0f, 2.0f, 3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float z[3];
        float expected[] = {5.0f, 7.0f, 9.0f};
        
        add_arrays(n, x, y, z);
        
        for (int i = 0; i < n; ++i) {
            assert(z[i] == expected[i]);
        }
    }

    // Test case 2: Addition with negative numbers
    {
        int n = 4;
        float x[] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float y[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float z[4];
        float expected[] = {0.0f, 0.0f, 0.0f, 0.0f};
        
        add_arrays(n, x, y, z);
        
        for (int i = 0; i < n; ++i) {
            assert(z[i] == expected[i]);
        }
    }

    // Test case 3: Addition with zero elements
    {
        int n = 0;
        float* x = nullptr;
        float* y = nullptr;
        float* z = nullptr;
        
        add_arrays(n, x, y, z);
        // No assertion needed as it should handle n=0 without issues
    }

    // Test case 4: Addition with large numbers
    {
        int n = 2;
        float x[] = {1.0e10f, 2.0e10f};
        float y[] = {3.0e10f, 4.0e10f};
        float z[2];
        float expected[] = {4.0e10f, 6.0e10f};
        
        add_arrays(n, x, y, z);
        
        for (int i = 0; i < n; ++i) {
            assert(z[i] == expected[i]);
        }
    }

    // Test case 5: Addition with decimal numbers
    {
        int n = 3;
        float x[] = {1.5f, 2.25f, 3.75f};
        float y[] = {0.5f, 0.75f, 1.25f};
        float z[3];
        float expected[] = {2.0f, 3.0f, 5.0f};
        
        add_arrays(n, x, y, z);
        
        for (int i = 0; i < n; ++i) {
            assert(z[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}