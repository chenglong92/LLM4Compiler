// original code(id = 198): 
 /*
__global__ void matrixMult ( float * A , float * B , float * C , int width ) { int k = 0 ; float sum = 0 ; int col = blockDim . x * blockIdx . x + threadIdx . x ; int row = blockDim . y * blockIdx . y + threadIdx . y ; if ( col < width && row < width ) { for ( k = 0 ; k < width ; k ++ ) sum += A [ row * width + k ] * B [ k * width + col ] ; C [ row * width + col ] = sum ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstring>

void matrixMult(float* A, float* B, float* C, int width) {
    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < width; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < width; ++k) {
                sum += A[row * width + k] * B[k * width + col];
            }
            C[row * width + col] = sum;
        }
    }
}

void testMatrixMult() {
    // Test case 1: 2x2 matrices
    {
        float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float B[] = {5.0f, 6.0f, 7.0f, 8.0f};
        float C[4];
        float expected[] = {19.0f, 22.0f, 43.0f, 50.0f};
        
        matrixMult(A, B, C, 2);
        
        for (int i = 0; i < 4; ++i) {
            assert(C[i] == expected[i]);
        }
    }

    // Test case 2: 1x1 matrices
    {
        float A[] = {2.0f};
        float B[] = {3.0f};
        float C[1];
        float expected[] = {6.0f};
        
        matrixMult(A, B, C, 1);
        
        assert(C[0] == expected[0]);
    }

    // Test case 3: 3x3 identity matrix multiplication
    {
        float A[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        float B[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        float C[9];
        
        matrixMult(A, B, C, 3);
        
        for (int i = 0; i < 9; ++i) {
            assert(C[i] == B[i]);
        }
    }

    // Test case 4: Zero matrix multiplication
    {
        float A[] = {0.0f, 0.0f, 0.0f, 0.0f};
        float B[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float C[4];
        float expected[] = {0.0f, 0.0f, 0.0f, 0.0f};
        
        matrixMult(A, B, C, 2);
        
        for (int i = 0; i < 4; ++i) {
            assert(C[i] == expected[i]);
        }
    }

    // Test case 5: 4x4 matrices
    {
        float A[] = {1.0f, 2.0f, 3.0f, 4.0f, 
                     5.0f, 6.0f, 7.0f, 8.0f, 
                     9.0f, 10.0f, 11.0f, 12.0f, 
                     13.0f, 14.0f, 15.0f, 16.0f};
        float B[] = {16.0f, 15.0f, 14.0f, 13.0f, 
                     12.0f, 11.0f, 10.0f, 9.0f, 
                     8.0f, 7.0f, 6.0f, 5.0f, 
                     4.0f, 3.0f, 2.0f, 1.0f};
        float C[16];
        float expected[] = {80.0f, 70.0f, 60.0f, 50.0f, 
                            240.0f, 214.0f, 188.0f, 162.0f, 
                            400.0f, 358.0f, 316.0f, 274.0f, 
                            560.0f, 502.0f, 444.0f, 386.0f};
        
        matrixMult(A, B, C, 4);
        
        for (int i = 0; i < 16; ++i) {
            assert(C[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testMatrixMult();
    return 0;
}