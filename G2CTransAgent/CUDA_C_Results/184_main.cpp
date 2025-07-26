// original code(id = 184): 
 /*
__global__ void vectorMatrixMult ( long int totalPixels , float * matrix , float * vector , float * out ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = blockDim . x * gridDim . x ; for ( long int i = index ; i < totalPixels ; i += stride ) { float sum = 0.0 ; for ( long int j = 0 ; j < totalPixels ; j ++ ) { sum += matrix [ i * totalPixels + j ] * vector [ j ] ; } out [ i ] = sum ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void vectorMatrixMult(long int totalPixels, float* matrix, float* vector, float* out) {
    for (long int i = 0; i < totalPixels; ++i) {
        float sum = 0.0;
        for (long int j = 0; j < totalPixels; ++j) {
            sum += matrix[i * totalPixels + j] * vector[j];
        }
        out[i] = sum;
    }
}

void testVectorMatrixMult() {
    // Test case 1: Basic functionality with 2x2 matrix and vector
    {
        long int totalPixels = 2;
        float matrix[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float vector[] = {5.0f, 6.0f};
        float out[2];
        float expected[] = {17.0f, 39.0f};
        
        vectorMatrixMult(totalPixels, matrix, vector, out);
        
        for (long int i = 0; i < totalPixels; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 2: Identity matrix multiplication
    {
        long int totalPixels = 3;
        float matrix[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        float vector[] = {1.0f, 2.0f, 3.0f};
        float out[3];
        float expected[] = {1.0f, 2.0f, 3.0f};
        
        vectorMatrixMult(totalPixels, matrix, vector, out);
        
        for (long int i = 0; i < totalPixels; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 3: Zero matrix multiplication
    {
        long int totalPixels = 2;
        float matrix[] = {0.0f, 0.0f, 0.0f, 0.0f};
        float vector[] = {1.0f, 2.0f};
        float out[2];
        float expected[] = {0.0f, 0.0f};
        
        vectorMatrixMult(totalPixels, matrix, vector, out);
        
        for (long int i = 0; i < totalPixels; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 4: Single element (1x1 matrix)
    {
        long int totalPixels = 1;
        float matrix[] = {5.0f};
        float vector[] = {3.0f};
        float out[1];
        float expected[] = {15.0f};
        
        vectorMatrixMult(totalPixels, matrix, vector, out);
        
        assert(out[0] == expected[0]);
    }

    // Test case 5: Large matrix (3x3) with negative values
    {
        long int totalPixels = 3;
        float matrix[] = {1.5f, -2.0f, 3.0f, -4.0f, 5.5f, -6.0f, 7.0f, -8.5f, 9.0f};
        float vector[] = {-1.0f, 2.0f, -3.0f};
        float out[3];
        float expected[] = {-14.5f, 29.0f, -43.5f};
        
        vectorMatrixMult(totalPixels, matrix, vector, out);
        
        for (long int i = 0; i < totalPixels; ++i) {
            assert(out[i] == expected[i]);
        }
    }
}

int main() {
    testVectorMatrixMult();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}