// original code(id = 37): 
 /*
__global__ void MulMatrixOnGPU ( float * A , float * B , float * C , int nx , int ny ) { int i = threadIdx . x + blockIdx . x * blockDim . x ; int j = threadIdx . y + blockIdx . y * blockDim . y ; int k ; if ( i < nx && j < ny ) { float sum = 0.0 ; for ( k = 0 ; k < nx ; k ++ ) { sum += A [ i * nx + k ] * B [ k * nx + j ] ; } C [ i * nx + j ] = sum ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void MulMatrixOnCPU(float* A, float* B, float* C, int nx, int ny) {
            for (int i = 0; i < nx; ++i) {
                for (int j = 0; j < ny; ++j) {
                    float sum = 0.0f;
                    for (int k = 0; k < nx; ++k) {
                        sum += A[i * nx + k] * B[k * nx + j];
                    }
                    C[i * nx + j] = sum;
                }
            }
        }

        void testMatrixMultiplication() {
            // Test case 1: 2x2 matrices
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[] = {5.0f, 6.0f, 7.0f, 8.0f};
                float C[4];
                float expected[] = {19.0f, 22.0f, 43.0f, 50.0f};
                
                MulMatrixOnCPU(A, B, C, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(C[i] - expected[i]) < 1e-6);
                }
            }

            // Test case 2: 1x1 matrices (edge case)
            {
                float A[] = {2.0f};
                float B[] = {3.0f};
                float C[1];
                float expected[] = {6.0f};
                
                MulMatrixOnCPU(A, B, C, 1, 1);
                
                assert(fabs(C[0] - expected[0]) < 1e-6);
            }

            // Test case 3: 3x3 matrices with zeros
            {
                float A[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
                float B[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
                float C[9];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
                
                MulMatrixOnCPU(A, B, C, 3, 3);
                
                for (int i = 0; i < 9; ++i) {
                    assert(fabs(C[i] - expected[i]) < 1e-6);
                }
            }

            // Test case 4: 2x3 and 3x2 matrices (non-square)
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float B[] = {7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
                float C[4];
                float expected[] = {58.0f, 64.0f, 139.0f, 154.0f};
                
                MulMatrixOnCPU(A, B, C, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(C[i] - expected[i]) < 1e-6);
                }
            }
        }

        int main() {
            testMatrixMultiplication();
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }