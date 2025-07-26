// original code(id = 4): 
 /*
__global__ void vectorMatrixMult ( long int totalPixels , int availablePixels , int outPixelOffset , float * matrix , float * vector , float * out ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = blockDim . x * gridDim . x ; for ( long int i = index ; i < availablePixels ; i += stride ) { float sum = 0.0 ; for ( long int j = 0 ; j < totalPixels ; j ++ ) { sum += matrix [ i * totalPixels + j ] * vector [ j ] ; } out [ i + outPixelOffset ] = sum ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

void vectorMatrixMult(long int totalPixels, int availablePixels, int outPixelOffset, float* matrix, float* vector, float* out);

int main() {
    // Test Case 1: Basic functionality test
    {
        const long int totalPixels = 3;
        const int availablePixels = 2;
        const int outPixelOffset = 1;
        float matrix[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
        float vector[3] = {1.0f, 2.0f, 3.0f};
        float out[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        
        vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
        
        assert(out[0] == 0.0f);
        assert(out[1] == 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f);
        assert(out[2] == 4.0f*1.0f + 5.0f*2.0f + 6.0f*3.0f);
        assert(out[3] == 0.0f);
    }

    // Test Case 2: Edge case with zero availablePixels
    {
        const long int totalPixels = 3;
        const int availablePixels = 0;
        const int outPixelOffset = 0;
        float matrix[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
        float vector[3] = {1.0f, 2.0f, 3.0f};
        float out[3] = {0.0f, 0.0f, 0.0f};
        
        vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
        
        assert(out[0] == 0.0f);
        assert(out[1] == 0.0f);
        assert(out[2] == 0.0f);
    }

    // Test Case 3: Large values test
    {
        const long int totalPixels = 1000;
        const int availablePixels = 500;
        const int outPixelOffset = 100;
        float* matrix = new float[totalPixels * availablePixels];
        float* vector = new float[totalPixels];
        float* out = new float[availablePixels + outPixelOffset + 100];
        
        // Initialize with large values
        for (long int i = 0; i < totalPixels * availablePixels; ++i) {
            matrix[i] = 1000.0f;
        }
        for (long int i = 0; i < totalPixels; ++i) {
            vector[i] = 1000.0f;
        }
        for (long int i = 0; i < availablePixels + outPixelOffset + 100; ++i) {
            out[i] = 0.0f;
        }
        
        vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
        
        // Verify results
        for (int i = 0; i < outPixelOffset; ++i) {
            assert(out[i] == 0.0f);
        }
        for (int i = outPixelOffset; i < availablePixels + outPixelOffset; ++i) {
            assert(out[i] == 1000.0f * 1000.0f * totalPixels);
        }
        for (int i = availablePixels + outPixelOffset; i < availablePixels + outPixelOffset + 100; ++i) {
            assert(out[i] == 0.0f);
        }
        
        delete[] matrix;
        delete[] vector;
        delete[] out;
    }

    // Test Case 4: Random values test
    {
        srand(time(0));
        const long int totalPixels = 10;
        const int availablePixels = 5;
        const int outPixelOffset = 2;
        float matrix[50];
        float vector[10];
        float out[20] = {0.0f};
        
        // Initialize with random values
        for (long int i = 0; i < 50; ++i) {
            matrix[i] = static_cast<float>(rand() % 100) / 10.0f;
        }
        for (long int i = 0; i < 10; ++i) {
            vector[i] = static_cast<float>(rand() % 100) / 10.0f;
        }
        
        vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
        
        // Manually calculate expected results and verify
        for (int i = 0; i < availablePixels; ++i) {
            float sum = 0.0f;
            for (long int j = 0; j < totalPixels; ++j) {
                sum += matrix[i * totalPixels + j] * vector[j];
            }
            assert(out[i + outPixelOffset] == sum);
        }
    }

    // Test Case 5: Negative values test
    {
        const long int totalPixels = 4;
        const int availablePixels = 2;
        const int outPixelOffset = 0;
        float matrix[8] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f, -7.0f, -8.0f};
        float vector[4] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float out[2] = {0.0f, 0.0f};
        
        vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
        
        assert(out[0] == (-1.0f*-1.0f) + (-2.0f*-2.0f) + (-3.0f*-3.0f) + (-4.0f*-4.0f));
        assert(out[1] == (-5.0f*-1.0f) + (-6.0f*-2.0f) + (-7.0f*-3.0f) + (-8.0f*-4.0f));
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}