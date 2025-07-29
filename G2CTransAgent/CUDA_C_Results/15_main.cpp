// original code(id = 15): 
 /*
__global__ void gpuMatrMultD ( float * Ad , float * Bd , float * Cd , int rowsA , int colsA , int colsB ) { int bIndx = blockIdx . x ; int bIndy = blockIdx . y ; int tIndx = threadIdx . x ; int tIndy = threadIdx . y ; Cd [ ( blockDim . x * bIndx + tIndx ) * colsB + blockDim . y * bIndy + tIndy ] = 0 ; for ( int k = 0 ; k < colsA ; ++ k ) { Cd [ ( blockDim . x * bIndx + tIndx ) * colsB + blockDim . y * bIndy + tIndy ] += Ad [ ( blockDim . x * bIndx + tIndx ) * colsA + k ] * Bd [ k * colsB + blockDim . y * bIndy + tIndy ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void cpuMatrMultD(float* Ad, float* Bd, float* Cd, int rowsA, int colsA, int colsB) {
            for (int i = 0; i < rowsA; ++i) {
                for (int j = 0; j < colsB; ++j) {
                    Cd[i * colsB + j] = 0;
                    for (int k = 0; k < colsA; ++k) {
                        Cd[i * colsB + j] += Ad[i * colsA + k] * Bd[k * colsB + j];
                    }
                }
            }
        }

        void testMatrixMultiplication() {
            // Test case 1: Basic 2x2 matrix multiplication
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[] = {5.0f, 6.0f, 7.0f, 8.0f};
                float C[4];
                float expected[] = {19.0f, 22.0f, 43.0f, 50.0f};
                
                cpuMatrMultD(A, B, C, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            // Test case 2: Rectangular matrices (2x3 * 3x2)
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float B[] = {7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
                float C[4];
                float expected[] = {58.0f, 64.0f, 139.0f, 154.0f};
                
                cpuMatrMultD(A, B, C, 2, 3, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            // Test case 3: Edge case - 1x1 matrices
            {
                float A[] = {5.0f};
                float B[] = {10.0f};
                float C[1];
                float expected[] = {50.0f};
                
                cpuMatrMultD(A, B, C, 1, 1, 1);
                
                assert(C[0] == expected[0]);
            }

            // Test case 4: Edge case - multiplication by zero matrix
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[] = {0.0f, 0.0f, 0.0f, 0.0f};
                float C[4];
                float expected[] = {0.0f, 0.0f, 0.0f, 0.0f};
                
                cpuMatrMultD(A, B, C, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            // Test case 5: Edge case - identity matrix multiplication
            {
                float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float B[] = {1.0f, 0.0f, 0.0f, 1.0f};
                float C[4];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
                
                cpuMatrMultD(A, B, C, 2, 2, 2);
                
                for (int i = 0; i < 4; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            testMatrixMultiplication();
            return 0;
        }