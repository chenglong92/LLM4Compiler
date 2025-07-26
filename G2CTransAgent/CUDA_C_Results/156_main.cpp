// original code(id = 156): 
 /*
__global__ void allLog2Kernel ( const double * arr , double * buf , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { buf [ i ] = arr [ i ] / 2 ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void allLog2Kernel(const double* arr, double* buf, int n) {
    for (int i = 0; i < n; ++i) {
        buf[i] = arr[i] / 2;
    }
}

void test_allLog2Kernel() {
    // Test case 1: Basic functionality
    {
        const double arr[] = {2.0, 4.0, 8.0, 16.0};
        double buf[4];
        allLog2Kernel(arr, buf, 4);
        assert(buf[0] == 1.0);
        assert(buf[1] == 2.0);
        assert(buf[2] == 4.0);
        assert(buf[3] == 8.0);
    }

    // Test case 2: Negative numbers
    {
        const double arr[] = {-2.0, -4.0, -8.0};
        double buf[3];
        allLog2Kernel(arr, buf, 3);
        assert(buf[0] == -1.0);
        assert(buf[1] == -2.0);
        assert(buf[2] == -4.0);
    }

    // Test case 3: Zero values
    {
        const double arr[] = {0.0, 0.0, 0.0};
        double buf[3];
        allLog2Kernel(arr, buf, 3);
        assert(buf[0] == 0.0);
        assert(buf[1] == 0.0);
        assert(buf[2] == 0.0);
    }

    // Test case 4: Single element
    {
        const double arr[] = {42.0};
        double buf[1];
        allLog2Kernel(arr, buf, 1);
        assert(buf[0] == 21.0);
    }

    // Test case 5: Large numbers
    {
        const double arr[] = {1e20, 2e20, 3e20};
        double buf[3];
        allLog2Kernel(arr, buf, 3);
        assert(buf[0] == 5e19);
        assert(buf[1] == 1e20);
        assert(buf[2] == 1.5e20);
    }

    // Test case 6: Small numbers
    {
        const double arr[] = {1e-20, 2e-20, 3e-20};
        double buf[3];
        allLog2Kernel(arr, buf, 3);
        assert(buf[0] == 5e-21);
        assert(buf[1] == 1e-20);
        assert(buf[2] == 1.5e-20);
    }

    // Test case 7: Empty array (should handle gracefully)
    {
        const double arr[] = {};
        double buf[0];
        allLog2Kernel(arr, buf, 0);
        // No assertions needed as it shouldn't crash
    }

    // Test case 8: Mixed positive and negative numbers
    {
        const double arr[] = {-1.0, 1.0, -2.0, 2.0};
        double buf[4];
        allLog2Kernel(arr, buf, 4);
        assert(buf[0] == -0.5);
        assert(buf[1] == 0.5);
        assert(buf[2] == -1.0);
        assert(buf[3] == 1.0);
    }

    std::cout << "All tests passed successfully!" << std::endl;
}

int main() {
    test_allLog2Kernel();
    return 0;
}