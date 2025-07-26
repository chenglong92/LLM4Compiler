// original code(id = 87): 
 /*
__global__ void gpu_matrix_transpose ( int * mat_in , int * mat_out , unsigned int rows , unsigned int cols ) { unsigned int idx = blockIdx . x * blockDim . x + threadIdx . x ; unsigned int idy = blockIdx . y * blockDim . y + threadIdx . y ; if ( idx < cols && idy < rows ) { unsigned int pos = idy * cols + idx ; unsigned int trans_pos = idx * rows + idy ; mat_out [ trans_pos ] = mat_in [ pos ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void cpu_matrix_transpose(int* mat_in, int* mat_out, unsigned int rows, unsigned int cols);

        int main() {
            // Test case 1: Square matrix
            {
                int mat_in[] = {1, 2, 3, 4};
                int mat_out[4];
                unsigned int rows = 2;
                unsigned int cols = 2;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                
                assert(mat_out[0] == 1);
                assert(mat_out[1] == 3);
                assert(mat_out[2] == 2);
                assert(mat_out[3] == 4);
            }
            
            // Test case 2: Rectangular matrix (rows > cols)
            {
                int mat_in[] = {1, 2, 3, 4, 5, 6};
                int mat_out[6];
                unsigned int rows = 3;
                unsigned int cols = 2;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                
                assert(mat_out[0] == 1);
                assert(mat_out[1] == 3);
                assert(mat_out[2] == 5);
                assert(mat_out[3] == 2);
                assert(mat_out[4] == 4);
                assert(mat_out[5] == 6);
            }
            
            // Test case 3: Rectangular matrix (cols > rows)
            {
                int mat_in[] = {1, 2, 3, 4, 5, 6};
                int mat_out[6];
                unsigned int rows = 2;
                unsigned int cols = 3;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                
                assert(mat_out[0] == 1);
                assert(mat_out[1] == 4);
                assert(mat_out[2] == 2);
                assert(mat_out[3] == 5);
                assert(mat_out[4] == 3);
                assert(mat_out[5] == 6);
            }
            
            // Test case 4: Single row matrix
            {
                int mat_in[] = {1, 2, 3};
                int mat_out[3];
                unsigned int rows = 1;
                unsigned int cols = 3;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                
                assert(mat_out[0] == 1);
                assert(mat_out[1] == 2);
                assert(mat_out[2] == 3);
            }
            
            // Test case 5: Single column matrix
            {
                int mat_in[] = {1, 2, 3};
                int mat_out[3];
                unsigned int rows = 3;
                unsigned int cols = 1;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                
                assert(mat_out[0] == 1);
                assert(mat_out[1] == 2);
                assert(mat_out[2] == 3);
            }
            
            // Test case 6: Empty matrix
            {
                int mat_in[] = {};
                int mat_out[] = {};
                unsigned int rows = 0;
                unsigned int cols = 0;
                
                cpu_matrix_transpose(mat_in, mat_out, rows, cols);
                // No assertions as there's no data to check
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }