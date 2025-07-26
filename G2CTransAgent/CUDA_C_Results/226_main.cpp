// original code(id = 226): 
 /*
__global__ void allDivInplaceKernel ( double * arr , double alpha , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { arr [ i ] /= alpha ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void allDivInplace(double* arr, double alpha, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] /= alpha;
    }
}

void testAllDivInplace() {
    // Test case 1: Divide by positive alpha
    {
        double arr[] = {2.0, 4.0, 6.0};
        double alpha = 2.0;
        int n = 3;
        allDivInplace(arr, alpha, n);
        assert(arr[0] == 1.0);
        assert(arr[1] == 2.0);
        assert(arr[2] == 3.0);
    }

    // Test case 2: Divide by negative alpha
    {
        double arr[] = {3.0, -6.0, 9.0};
        double alpha = -3.0;
        int n = 3;
        allDivInplace(arr, alpha, n);
        assert(arr[0] == -1.0);
        assert(arr[1] == 2.0);
        assert(arr[2] == -3.0);
    }

    // Test case 3: Divide by zero (should produce inf or -inf)
    {
        double arr[] = {1.0, -1.0, 0.0};
        double alpha = 0.0;
        int n = 3;
        allDivInplace(arr, alpha, n);
        assert(std::isinf(arr[0]) && arr[0] > 0);
        assert(std::isinf(arr[1]) && arr[1] < 0);
        assert(std::isnan(arr[2])); // 0.0/0.0 is NaN
    }

    // Test case 4: Empty array
    {
        double arr[] = {};
        double alpha = 5.0;
        int n = 0;
        allDivInplace(arr, alpha, n);
        // No elements to check, just ensure no crash
    }

    // Test case 5: Large array
    {
        const int n = 1000;
        double arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = i * 2.0;
        }
        double alpha = 2.0;
        allDivInplace(arr, alpha, n);
        for (int i = 0; i < n; ++i) {
            assert(arr[i] == i);
        }
    }
}

int main() {
    testAllDivInplace();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}