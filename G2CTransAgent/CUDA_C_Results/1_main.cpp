// original code(id = 1): 
 /*
__global__ void naive_sgemm_kernel ( float * C , float * A , float * B , long size ) { const long i = blockIdx . x * blockDim . x + threadIdx . x ; const long j = blockIdx . y * blockDim . y + threadIdx . y ; float val = 0.0 ; if ( i >= size || j >= size ) return ; for ( long k = 0 ; k < size ; k ++ ) { val += A [ i * size + k ] * B [ k * size + j ] ; } C [ i * size + j ] += val ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void naive_sgemm(float* C, float* A, float* B, long size) {
            for (long i = 0; i < size; ++i) {
                for (long j = 0; j < size; ++j) {
                    float val = 0.0;
                    for (long k = 0; k < size; ++k) {
                        val += A[i * size + k] * B[k * size + j];
                    }
                    C[i * size + j] += val;
                }
            }
        }

        bool compare_matrices(float* A, float* B, long size, float epsilon = 1e-6) {
            for (long i = 0; i < size * size; ++i) {
                if (std::abs(A[i] - B[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        void print_matrix(float* mat, long size) {
            for (long i = 0; i < size; ++i) {
                for (long j = 0; j < size; ++j) {
                    std::cout << mat[i * size + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        void test_naive_sgemm() {
            // Test case 1: 2x2 matrices
            {
                const long size = 2;
                float A[size * size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[size * size] = {5.0f, 6.0f, 7.0f, 8.0f};
                float C[size * size] = {0.0f};
                float expected[size * size] = {19.0f, 22.0f, 43.0f, 50.0f};

                naive_sgemm(C, A, B, size);
                assert(compare_matrices(C, expected, size));
            }

            // Test case 2: 3x3 identity matrix multiplication
            {
                const long size = 3;
                float A[size * size] = {1.0f, 0.0f, 0.0f, 
                                       0.0f, 1.0f, 0.0f, 
                                       0.0f, 0.0f, 1.0f};
                float B[size * size] = {1.0f, 2.0f, 3.0f, 
                                       4.0f, 5.0f, 6.0f, 
                                       7.0f, 8.0f, 9.0f};
                float C[size * size] = {0.0f};
                float expected[size * size] = {1.0f, 2.0f, 3.0f, 
                                              4.0f, 5.0f, 6.0f, 
                                              7.0f, 8.0f, 9.0f};

                naive_sgemm(C, A, B, size);
                assert(compare_matrices(C, expected, size));
            }

            // Test case 3: 1x1 matrix
            {
                const long size = 1;
                float A[size * size] = {2.0f};
                float B[size * size] = {3.0f};
                float C[size * size] = {1.0f};
                float expected[size * size] = {7.0f};

                naive_sgemm(C, A, B, size);
                assert(compare_matrices(C, expected, size));
            }

            // Test case 4: Zero matrices
            {
                const long size = 2;
                float A[size * size] = {0.0f};
                float B[size * size] = {0.0f};
                float C[size * size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float expected[size * size] = {1.0f, 2.0f, 3.0f, 4.0f};

                naive_sgemm(C, A, B, size);
                assert(compare_matrices(C, expected, size));
            }

            // Test case 5: Accumulation test
            {
                const long size = 2;
                float A[size * size] = {1.0f, 1.0f, 1.0f, 1.0f};
                float B[size * size] = {1.0f, 1.0f, 1.0f, 1.0f};
                float C[size * size] = {1.0f, 1.0f, 1.0f, 1.0f};
                float expected[size * size] = {3.0f, 3.0f, 3.0f, 3.0f};

                naive_sgemm(C, A, B, size);
                assert(compare_matrices(C, expected, size));
            }

            std::cout << "All tests passed!" << std::endl;
        }

        int main() {
            test_naive_sgemm();
            return 0;
        }