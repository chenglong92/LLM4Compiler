// original code(id = 100): 
 /*
__global__ void mmul ( const float * A , const float * B , float * C , int r1 , int c1 , int r2 , int c2 ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; int idy = threadIdx . y + blockDim . y * blockIdx . y ; if ( ( idx < c2 ) && ( idy < c1 ) ) { float temp = 0 ; for ( int i = 0 ; i < c1 ; i ++ ) temp += A [ idy * c1 + i ] * B [ i * c2 + idx ] ; C [ idy * c2 + idx ] = temp ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void mmul(const float* A, const float* B, float* C, int r1, int c1, int r2, int c2) {
    for (int idy = 0; idy < r1; ++idy) {
        for (int idx = 0; idx < c2; ++idx) {
            float temp = 0;
            for (int i = 0; i < c1; ++i) {
                temp += A[idy * c1 + i] * B[i * c2 + idx];
            }
            C[idy * c2 + idx] = temp;
        }
    }
}

void printMatrix(const float* matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Test case 1: 2x2 matrices
    {
        float A[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float B[] = {5.0f, 6.0f, 7.0f, 8.0f};
        float C[4];
        mmul(A, B, C, 2, 2, 2, 2);
        assert(C[0] == 19.0f);
        assert(C[1] == 22.0f);
        assert(C[2] == 43.0f);
        assert(C[3] == 50.0f);
    }

    // Test case 2: 1x1 matrices
    {
        float A[] = {2.0f};
        float B[] = {3.0f};
        float C[1];
        mmul(A, B, C, 1, 1, 1, 1);
        assert(C[0] == 6.0f);
    }

    // Test case 3: Identity matrix multiplication
    {
        float A[] = {1.0f, 0.0f, 0.0f, 1.0f};
        float B[] = {1.0f, 0.0f, 0.0f, 1.0f};
        float C[4];
        mmul(A, B, C, 2, 2, 2, 2);
        assert(C[0] == 1.0f);
        assert(C[1] == 0.0f);
        assert(C[2] == 0.0f);
        assert(C[3] == 1.0f);
    }

    // Test case 4: Zero matrix multiplication
    {
        float A[] = {0.0f, 0.0f, 0.0f, 0.0f};
        float B[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float C[4];
        mmul(A, B, C, 2, 2, 2, 2);
        assert(C[0] == 0.0f);
        assert(C[1] == 0.0f);
        assert(C[2] == 0.0f);
        assert(C[3] == 0.0f);
    }

    // Test case 5: 3x2 and 2x3 matrices
    {
        float A[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
        float B[] = {7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
        float C[9];
        mmul(A, B, C, 3, 2, 2, 3);
        assert(C[0] == 27.0f);
        assert(C[1] == 30.0f);
        assert(C[2] == 33.0f);
        assert(C[3] == 61.0f);
        assert(C[4] == 68.0f);
        assert(C[5] == 75.0f);
        assert(C[6] == 95.0f);
        assert(C[7] == 106.0f);
        assert(C[8] == 117.0f);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}