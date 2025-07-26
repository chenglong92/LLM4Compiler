// original code(id = 109): 
 /*
__global__ void matrixMultiply ( float * A , float * B , float * C , int numARows , int numAColumns , int numBRows , int numBColumns ) { int row = blockIdx . y * blockDim . y + threadIdx . y ; int col = blockIdx . x * blockDim . x + threadIdx . x ; int numCRows = numARows ; int numCColumns = numBColumns ; if ( row < numCRows && col < numCColumns ) { float sum = 0 ; for ( int k = 0 ; k < numBRows ; k ++ ) { sum += A [ row * numAColumns + k ] * B [ k * numBColumns + col ] ; } C [ row * numCColumns + col ] = sum ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matrixMultiply(float* A, float* B, float* C, int numARows, int numAColumns, int numBRows, int numBColumns) {
            int numCRows = numARows;
            int numCColumns = numBColumns;

            for (int row = 0; row < numCRows; ++row) {
                for (int col = 0; col < numCColumns; ++col) {
                    float sum = 0.0f;
                    for (int k = 0; k < numBRows; ++k) {
                        sum += A[row * numAColumns + k] * B[k * numBColumns + col];
                    }
                    C[row * numCColumns + col] = sum;
                }
            }
        }

        int main() {
            // Test case 1: Normal case (3x2 matrix multiplied by 2x4 matrix)
            {
                const int numARows = 3, numAColumns = 2;
                const int numBRows = 2, numBColumns = 4;
                float A[] = {1, 2, 3, 4, 5, 6};
                float B[] = {1, 2, 3, 4, 5, 6, 7, 8};
                float C[numARows * numBColumns];
                float expected[] = {11, 14, 17, 20, 23, 30, 37, 44, 35, 46, 57, 68};

                matrixMultiply(A, B, C, numARows, numAColumns, numBRows, numBColumns);

                for (int i = 0; i < numARows * numBColumns; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            // Test case 2: Edge case (1x1 matrix multiplied by 1x1 matrix)
            {
                const int numARows = 1, numAColumns = 1;
                const int numBRows = 1, numBColumns = 1;
                float A[] = {2};
                float B[] = {3};
                float C[numARows * numBColumns];
                float expected[] = {6};

                matrixMultiply(A, B, C, numARows, numAColumns, numBRows, numBColumns);

                assert(C[0] == expected[0]);
            }

            // Test case 3: Edge case (2x3 matrix multiplied by 3x1 matrix)
            {
                const int numARows = 2, numAColumns = 3;
                const int numBRows = 3, numBColumns = 1;
                float A[] = {1, 2, 3, 4, 5, 6};
                float B[] = {1, 2, 3};
                float C[numARows * numBColumns];
                float expected[] = {14, 32};

                matrixMultiply(A, B, C, numARows, numAColumns, numBRows, numBColumns);

                for (int i = 0; i < numARows * numBColumns; ++i) {
                    assert(C[i] == expected[i]);
                }
            }

            // Test case 4: Edge case (0x0 matrix - should not crash)
            {
                const int numARows = 0, numAColumns = 0;
                const int numBRows = 0, numBColumns = 0;
                float* A = nullptr;
                float* B = nullptr;
                float* C = nullptr;

                matrixMultiply(A, B, C, numARows, numAColumns, numBRows, numBColumns);
                // No assertion as we're just checking it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }