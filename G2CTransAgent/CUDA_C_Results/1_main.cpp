// original code(id = 1): 
 /*
__global__ void naive_sgemm_kernel ( float * C , float * A , float * B , long size ) { const long i = blockIdx . x * blockDim . x + threadIdx . x ; const long j = blockIdx . y * blockDim . y + threadIdx . y ; float val = 0.0 ; if ( i >= size || j >= size ) return ; for ( long k = 0 ; k < size ; k ++ ) { val += A [ i * size + k ] * B [ k * size + j ] ; } C [ i * size + j ] += val ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void naive_sgemm(float* C, float* A, float* B, long size) {
            for (long i = 0; i < size; ++i) {
                for (long j = 0; j < size; ++j) {
                    float val = 0.0f;
                    for (long k = 0; k < size; ++k) {
                        val += A[i * size + k] * B[k * size + j];
                    }
                    C[i * size + j] += val;
                }
            }
        }

        void test_naive_sgemm() {
            // Test case 1: 1x1 matrices
            {
                float A[] = {2.0f};
                float B[] = {3.0f};
                float C[] = {0.0f};
                float expected[] = {6.0f};
                naive_sgemm(C, A, B, 1);
                assert(std::abs(C[0] - expected[0]) < 1e-6);
            }

            // Test case 2: 2x2 matrices
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[] = {5.0f, 6.0f, 7.0f, 8.0f};
                float C[] = {0.0f, 0.0f, 0.0f, 0.0f};
                float expected[] = {19.0f, 22.0f, 43.0f, 50.0f};
                naive_sgemm(C, A, B, 2);
                for (int i = 0; i < 4; ++i) {
                    assert(std::abs(C[i] - expected[i]) < 1e-6);
                }
            }

            // Test case 3: 3x3 matrices with non-zero initial C
            {
                float A[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
                float B[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
                float C[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
                float expected[] = {2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
                naive_sgemm(C, A, B, 3);
                for (int i = 0; i < 9; ++i) {
                    assert(std::abs(C[i] - expected[i]) < 1e-6);
                }
            }

            // Test case 4: 4x4 identity matrix multiplication
            {
                float A[] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
                float B[] = {1.0f, 2.0f, 3.0f, 4.0f,
                             5.0f, 6.0f, 7.0f, 8.0f,
                             9.0f, 10.0f, 11.0f, 12.0f,
                             13.0f, 14.0f, 15.0f, 16.0f};
                float C[] = {0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 0.0f};
                naive_sgemm(C, A, B, 4);
                for (int i = 0; i < 16; ++i) {
                    assert(std::abs(C[i] - B[i]) < 1e-6);
                }
            }
        }

        int main() {
            test_naive_sgemm();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }