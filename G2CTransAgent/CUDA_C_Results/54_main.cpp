// original code(id = 54): 
 /*
__global__ void gpu_matrix_mult ( int * a , int * b , int * c , int m , int n , int k ) { int row = blockIdx . y * blockDim . y + threadIdx . y ; int col = blockIdx . x * blockDim . x + threadIdx . x ; int sum = 0 ; if ( col < k && row < m ) { for ( int i = 0 ; i < n ; i ++ ) { sum += a [ row * n + i ] * b [ i * k + col ] ; } c [ row * k + col ] = sum ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void cpu_matrix_mult(int* a, int* b, int* c, int m, int n, int k) {
            for (int row = 0; row < m; ++row) {
                for (int col = 0; col < k; ++col) {
                    int sum = 0;
                    for (int i = 0; i < n; ++i) {
                        sum += a[row * n + i] * b[i * k + col];
                    }
                    c[row * k + col] = sum;
                }
            }
        }

        int main() {
            // Test case 1: Normal case (3x2 matrix multiplied by 2x3 matrix)
            {
                const int m = 3, n = 2, k = 3;
                int a[m*n] = {1, 2, 3, 4, 5, 6};
                int b[n*k] = {7, 8, 9, 10, 11, 12};
                int c[m*k] = {0};
                int expected[m*k] = {27, 30, 33, 61, 68, 75, 95, 106, 117};
                
                cpu_matrix_mult(a, b, c, m, n, k);
                
                for (int i = 0; i < m*k; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 2: Edge case - multiplying 1x1 matrices
            {
                const int m = 1, n = 1, k = 1;
                int a[m*n] = {5};
                int b[n*k] = {7};
                int c[m*k] = {0};
                int expected[m*k] = {35};
                
                cpu_matrix_mult(a, b, c, m, n, k);
                
                assert(c[0] == expected[0]);
            }

            // Test case 3: Edge case - multiplying with zero elements (should still work)
            {
                const int m = 2, n = 3, k = 2;
                int a[m*n] = {0, 0, 0, 0, 0, 0};
                int b[n*k] = {0, 0, 0, 0, 0, 0};
                int c[m*k] = {0};
                int expected[m*k] = {0, 0, 0, 0};
                
                cpu_matrix_mult(a, b, c, m, n, k);
                
                for (int i = 0; i < m*k; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 4: Edge case - multiplying rectangular matrices (1x3 and 3x1)
            {
                const int m = 1, n = 3, k = 1;
                int a[m*n] = {1, 2, 3};
                int b[n*k] = {4, 5, 6};
                int c[m*k] = {0};
                int expected[m*k] = {32};
                
                cpu_matrix_mult(a, b, c, m, n, k);
                
                assert(c[0] == expected[0]);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }