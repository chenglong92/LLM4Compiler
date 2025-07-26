// original code(id = 96): 
 /*
__global__ void matrixMultiplication ( int * dev_a , int * dev_b , int * dev_c , int row_a , int col_a , int col_b ) { int row = threadIdx . y + blockIdx . y * blockDim . y ; int col = threadIdx . x + blockIdx . x * blockDim . x ; int ret = 0 ; if ( row < row_a && col < col_b ) { for ( int i = 0 ; i < col_a ; ++ i ) { ret += dev_a [ row * col_a + i ] * dev_b [ i * col_b + col ] ; } dev_c [ row * col_b + col ] = ret ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matrixMultiplication(int* dev_a, int* dev_b, int* dev_c, int row_a, int col_a, int col_b);

        int main() {
            // Test case 1: Normal case - 2x2 matrices
            {
                int a[] = {1, 2, 3, 4};
                int b[] = {5, 6, 7, 8};
                int c[4];
                int expected[] = {19, 22, 43, 50};
                
                matrixMultiplication(a, b, c, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }
            
            // Test case 2: Normal case - rectangular matrices (2x3 * 3x2)
            {
                int a[] = {1, 2, 3, 4, 5, 6};
                int b[] = {7, 8, 9, 10, 11, 12};
                int c[4];
                int expected[] = {58, 64, 139, 154};
                
                matrixMultiplication(a, b, c, 2, 3, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }
            
            // Test case 3: Edge case - identity matrix multiplication
            {
                int a[] = {1, 0, 0, 1};
                int b[] = {1, 0, 0, 1};
                int c[4];
                int expected[] = {1, 0, 0, 1};
                
                matrixMultiplication(a, b, c, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }
            
            // Test case 4: Edge case - multiplication by zero matrix
            {
                int a[] = {1, 2, 3, 4};
                int b[] = {0, 0, 0, 0};
                int c[4];
                int expected[] = {0, 0, 0, 0};
                
                matrixMultiplication(a, b, c, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }
            
            // Test case 5: Edge case - single element matrices
            {
                int a[] = {5};
                int b[] = {7};
                int c[1];
                int expected[] = {35};
                
                matrixMultiplication(a, b, c, 1, 1, 1);
                
                assert(c[0] == expected[0]);
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }