// original code(id = 93): 
 /*
__global__ void matDiagAddInplaceKernel ( double * mat , double alpha , int dim ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < dim ) { mat [ i * dim + i ] += alpha ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matDiagAddInplace(double* mat, double alpha, int dim) {
            for (int i = 0; i < dim; ++i) {
                mat[i * dim + i] += alpha;
            }
        }

        void printMatrix(double* mat, int dim) {
            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) {
                    std::cout << mat[i * dim + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        int main() {
            // Test case 1: 2x2 matrix with positive alpha
            {
                double mat[4] = {1.0, 2.0, 3.0, 4.0};
                double alpha = 5.0;
                int dim = 2;
                matDiagAddInplace(mat, alpha, dim);
                assert(mat[0] == 6.0);
                assert(mat[1] == 2.0);
                assert(mat[2] == 3.0);
                assert(mat[3] == 9.0);
            }

            // Test case 2: 3x3 matrix with negative alpha
            {
                double mat[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
                double alpha = -2.0;
                int dim = 3;
                matDiagAddInplace(mat, alpha, dim);
                assert(mat[0] == -1.0);
                assert(mat[4] == 3.0);
                assert(mat[8] == 7.0);
            }

            // Test case 3: 1x1 matrix with zero alpha
            {
                double mat[1] = {10.0};
                double alpha = 0.0;
                int dim = 1;
                matDiagAddInplace(mat, alpha, dim);
                assert(mat[0] == 10.0);
            }

            // Test case 4: 4x4 matrix with large alpha
            {
                double mat[16] = {0.0};
                double alpha = 1000.0;
                int dim = 4;
                matDiagAddInplace(mat, alpha, dim);
                for (int i = 0; i < dim; ++i) {
                    for (int j = 0; j < dim; ++j) {
                        if (i == j) {
                            assert(mat[i * dim + j] == alpha);
                        } else {
                            assert(mat[i * dim + j] == 0.0);
                        }
                    }
                }
            }

            // Test case 5: 2x2 matrix with fractional alpha
            {
                double mat[4] = {1.5, 2.5, 3.5, 4.5};
                double alpha = 0.5;
                int dim = 2;
                matDiagAddInplace(mat, alpha, dim);
                assert(mat[0] == 2.0);
                assert(mat[1] == 2.5);
                assert(mat[2] == 3.5);
                assert(mat[3] == 5.0);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }