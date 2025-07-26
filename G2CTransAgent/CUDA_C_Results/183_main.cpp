// original code(id = 183): 
 /*
__global__ void matrixTranspose ( int * in_mat , int * out_mat , int dim_rows , int dim_cols ) { int row = threadIdx . y + blockIdx . y * blockDim . y ; int col = threadIdx . x + blockIdx . x * blockDim . x ; if ( row < dim_rows && col < dim_cols ) { unsigned int new_pos = col * dim_cols + row ; out_mat [ new_pos ] = in_mat [ row * dim_cols + col ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matrixTranspose(int* in_mat, int* out_mat, int dim_rows, int dim_cols) {
            for (int row = 0; row < dim_rows; ++row) {
                for (int col = 0; col < dim_cols; ++col) {
                    unsigned int new_pos = col * dim_cols + row;
                    out_mat[new_pos] = in_mat[row * dim_cols + col];
                }
            }
        }

        void printMatrix(int* mat, int rows, int cols) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << mat[i * cols + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        int main() {
            // Test case 1: Square matrix
            {
                int in_mat[] = {1, 2, 3, 4};
                int out_mat[4];
                int dim_rows = 2;
                int dim_cols = 2;
                int expected[] = {1, 3, 2, 4};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            // Test case 2: Rectangular matrix (rows > cols)
            {
                int in_mat[] = {1, 2, 3, 4, 5, 6};
                int out_mat[6];
                int dim_rows = 3;
                int dim_cols = 2;
                int expected[] = {1, 3, 5, 2, 4, 6};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            // Test case 3: Rectangular matrix (cols > rows)
            {
                int in_mat[] = {1, 2, 3, 4, 5, 6};
                int out_mat[6];
                int dim_rows = 2;
                int dim_cols = 3;
                int expected[] = {1, 4, 2, 5, 3, 6};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            // Test case 4: Single row matrix
            {
                int in_mat[] = {1, 2, 3};
                int out_mat[3];
                int dim_rows = 1;
                int dim_cols = 3;
                int expected[] = {1, 2, 3};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            // Test case 5: Single column matrix
            {
                int in_mat[] = {1, 2, 3};
                int out_mat[3];
                int dim_rows = 3;
                int dim_cols = 1;
                int expected[] = {1, 2, 3};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            // Test case 6: Single element matrix
            {
                int in_mat[] = {42};
                int out_mat[1];
                int dim_rows = 1;
                int dim_cols = 1;
                int expected[] = {42};

                matrixTranspose(in_mat, out_mat, dim_rows, dim_cols);

                for (int i = 0; i < dim_rows * dim_cols; ++i) {
                    assert(out_mat[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }