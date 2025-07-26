// original code(id = 15): 
 /*
__global__ void gpuMatrMultD ( float * Ad , float * Bd , float * Cd , int rowsA , int colsA , int colsB ) { int bIndx = blockIdx . x ; int bIndy = blockIdx . y ; int tIndx = threadIdx . x ; int tIndy = threadIdx . y ; Cd [ ( blockDim . x * bIndx + tIndx ) * colsB + blockDim . y * bIndy + tIndy ] = 0 ; for ( int k = 0 ; k < colsA ; ++ k ) { Cd [ ( blockDim . x * bIndx + tIndx ) * colsB + blockDim . y * bIndy + tIndy ] += Ad [ ( blockDim . x * bIndx + tIndx ) * colsA + k ] * Bd [ k * colsB + blockDim . y * bIndy + tIndy ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
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

        bool compareMatrices(float* A, float* B, int rows, int cols, float epsilon = 1e-6) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (fabs(A[i * cols + j] - B[i * cols + j]) > epsilon) {
                        return false;
                    }
                }
            }
            return true;
        }

        void printMatrix(float* matrix, int rows, int cols) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << matrix[i * cols + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        void testSquareMatrices() {
            const int size = 3;
            float A[size * size] = {1.0f, 2.0f, 3.0f, 
                                   4.0f, 5.0f, 6.0f, 
                                   7.0f, 8.0f, 9.0f};
            float B[size * size] = {9.0f, 8.0f, 7.0f, 
                                   6.0f, 5.0f, 4.0f, 
                                   3.0f, 2.0f, 1.0f};
            float expected[size * size] = {30.0f, 24.0f, 18.0f, 
                                          84.0f, 69.0f, 54.0f, 
                                          138.0f, 114.0f, 90.0f};
            float C[size * size] = {0};

            cpuMatrMultD(A, B, C, size, size, size);

            assert(compareMatrices(C, expected, size, size));
            std::cout << "Square matrices test passed." << std::endl;
        }

        void testRectangularMatrices() {
            const int rowsA = 2, colsA = 3, colsB = 2;
            float A[rowsA * colsA] = {1.0f, 2.0f, 3.0f, 
                                     4.0f, 5.0f, 6.0f};
            float B[colsA * colsB] = {1.0f, 2.0f, 
                                     3.0f, 4.0f, 
                                     5.0f, 6.0f};
            float expected[rowsA * colsB] = {22.0f, 28.0f, 
                                            49.0f, 64.0f};
            float C[rowsA * colsB] = {0};

            cpuMatrMultD(A, B, C, rowsA, colsA, colsB);

            assert(compareMatrices(C, expected, rowsA, colsB));
            std::cout << "Rectangular matrices test passed." << std::endl;
        }

        void testIdentityMatrix() {
            const int size = 3;
            float A[size * size] = {1.0f, 2.0f, 3.0f, 
                                   4.0f, 5.0f, 6.0f, 
                                   7.0f, 8.0f, 9.0f};
            float I[size * size] = {1.0f, 0.0f, 0.0f, 
                                   0.0f, 1.0f, 0.0f, 
                                   0.0f, 0.0f, 1.0f};
            float C[size * size] = {0};

            cpuMatrMultD(A, I, C, size, size, size);

            assert(compareMatrices(C, A, size, size));
            std::cout << "Identity matrix test passed." << std::endl;
        }

        void testSingleElementMatrices() {
            const int size = 1;
            float A[size] = {5.0f};
            float B[size] = {7.0f};
            float expected[size] = {35.0f};
            float C[size] = {0};

            cpuMatrMultD(A, B, C, size, size, size);

            assert(compareMatrices(C, expected, size, size));
            std::cout << "Single element matrices test passed." << std::endl;
        }

        void testZeroMatrix() {
            const int rowsA = 2, colsA = 2, colsB = 2;
            float A[rowsA * colsA] = {0};
            float B[colsA * colsB] = {1.0f, 2.0f, 
                                     3.0f, 4.0f};
            float expected[rowsA * colsB] = {0};
            float C[rowsA * colsB] = {0};

            cpuMatrMultD(A, B, C, rowsA, colsA, colsB);

            assert(compareMatrices(C, expected, rowsA, colsB));
            std::cout << "Zero matrix test passed." << std::endl;
        }

        int main() {
            testSquareMatrices();
            testRectangularMatrices();
            testIdentityMatrix();
            testSingleElementMatrices();
            testZeroMatrix();

            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }