// original code(id = 146): 
 /*
__global__ void allMulInplaceKernel ( double * arr , double alpha , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { arr [ i ] *= alpha ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void allMulInplace(double* arr, double alpha, int n) {
            for (int i = 0; i < n; ++i) {
                arr[i] *= alpha;
            }
        }

        void test_allMulInplace() {
            // Test case 1: Multiply array with positive alpha
            {
                double arr[] = {1.0, 2.0, 3.0, 4.0};
                double alpha = 2.0;
                int n = sizeof(arr) / sizeof(arr[0]);
                double expected[] = {2.0, 4.0, 6.0, 8.0};
                allMulInplace(arr, alpha, n);
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 2: Multiply array with negative alpha
            {
                double arr[] = {1.0, -2.0, 3.0, -4.0};
                double alpha = -1.5;
                int n = sizeof(arr) / sizeof(arr[0]);
                double expected[] = {-1.5, 3.0, -4.5, 6.0};
                allMulInplace(arr, alpha, n);
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 3: Multiply array with zero alpha
            {
                double arr[] = {1.0, 2.0, 3.0, 4.0};
                double alpha = 0.0;
                int n = sizeof(arr) / sizeof(arr[0]);
                double expected[] = {0.0, 0.0, 0.0, 0.0};
                allMulInplace(arr, alpha, n);
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 4: Empty array (n = 0)
            {
                double arr[] = {};
                double alpha = 1.0;
                int n = 0;
                allMulInplace(arr, alpha, n);
                // No assertion needed as function should handle n=0 without issues
            }

            // Test case 5: Single element array
            {
                double arr[] = {5.0};
                double alpha = 3.0;
                int n = sizeof(arr) / sizeof(arr[0]);
                double expected[] = {15.0};
                allMulInplace(arr, alpha, n);
                for (int i = 0; i < n; ++i) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 6: Large array
            {
                const int large_size = 1000;
                double arr[large_size];
                double alpha = 0.5;
                for (int i = 0; i < large_size; ++i) {
                    arr[i] = i * 2.0;
                }
                allMulInplace(arr, alpha, large_size);
                for (int i = 0; i < large_size; ++i) {
                    assert(arr[i] == i * 2.0 * 0.5);
                }
            }
        }

        int main() {
            test_allMulInplace();
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }