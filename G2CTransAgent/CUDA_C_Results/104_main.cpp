// original code(id = 104): 
 /*
__global__ void allAddInplaceKernel ( double * arr , double alpha , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { arr [ i ] += alpha ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void allAddInplace(double* arr, double alpha, int n) {
            for (int i = 0; i < n; ++i) {
                arr[i] += alpha;
            }
        }

        int main() {
            // Test case 1: Normal case with positive alpha
            {
                const int n = 5;
                double arr[n] = {1.0, 2.0, 3.0, 4.0, 5.0};
                double alpha = 10.0;
                allAddInplace(arr, alpha, n);
                double expected[n] = {11.0, 12.0, 13.0, 14.0, 15.0};
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 2: Normal case with negative alpha
            {
                const int n = 5;
                double arr[n] = {10.0, 20.0, 30.0, 40.0, 50.0};
                double alpha = -5.0;
                allAddInplace(arr, alpha, n);
                double expected[n] = {5.0, 15.0, 25.0, 35.0, 45.0};
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 3: Edge case with empty array
            {
                const int n = 0;
                double arr[1] = {0.0}; // Dummy array
                double alpha = 100.0;
                allAddInplace(arr, alpha, n);
                // No operation should be performed
            }

            // Test case 4: Edge case with zero alpha
            {
                const int n = 3;
                double arr[n] = {1.5, 2.5, 3.5};
                double alpha = 0.0;
                allAddInplace(arr, alpha, n);
                double expected[n] = {1.5, 2.5, 3.5};
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 5: Large array
            {
                const int n = 1000;
                double arr[n];
                for (int i = 0; i < n; ++i) {
                    arr[i] = i;
                }
                double alpha = 0.5;
                allAddInplace(arr, alpha, n);
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == i + 0.5);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }