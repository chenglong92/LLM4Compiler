// original code(id = 4): 
 /*
__global__ void vectorMatrixMult ( long int totalPixels , int availablePixels , int outPixelOffset , float * matrix , float * vector , float * out ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = blockDim . x * gridDim . x ; for ( long int i = index ; i < availablePixels ; i += stride ) { float sum = 0.0 ; for ( long int j = 0 ; j < totalPixels ; j ++ ) { sum += matrix [ i * totalPixels + j ] * vector [ j ] ; } out [ i + outPixelOffset ] = sum ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void vectorMatrixMult(long int totalPixels, int availablePixels, int outPixelOffset, float* matrix, float* vector, float* out);

        int main() {
            // Test Case 1: Normal case with small values
            {
                const long int totalPixels = 3;
                const int availablePixels = 2;
                const int outPixelOffset = 1;
                
                float matrix[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float vector[] = {1.0f, 2.0f, 3.0f};
                float out[3] = {0.0f}; // Initialize with 0
                
                vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
                
                assert(out[0] == 0.0f); // Should remain unchanged
                assert(out[1] == 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f);
                assert(out[2] == 4.0f*1.0f + 5.0f*2.0f + 6.0f*3.0f);
            }
            
            // Test Case 2: Edge case with single element
            {
                const long int totalPixels = 1;
                const int availablePixels = 1;
                const int outPixelOffset = 0;
                
                float matrix[] = {2.0f};
                float vector[] = {3.0f};
                float out[1] = {0.0f};
                
                vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
                
                assert(out[0] == 2.0f * 3.0f);
            }
            
            // Test Case 3: Zero available pixels (should do nothing)
            {
                const long int totalPixels = 3;
                const int availablePixels = 0;
                const int outPixelOffset = 0;
                
                float matrix[] = {1.0f, 2.0f, 3.0f};
                float vector[] = {1.0f, 2.0f, 3.0f};
                float out[3] = {0.0f, 0.0f, 0.0f};
                
                vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
                
                assert(out[0] == 0.0f);
                assert(out[1] == 0.0f);
                assert(out[2] == 0.0f);
            }
            
            // Test Case 4: Large values
            {
                const long int totalPixels = 2;
                const int availablePixels = 2;
                const int outPixelOffset = 0;
                
                float matrix[] = {1000000.0f, 2000000.0f, 3000000.0f, 4000000.0f};
                float vector[] = {1000000.0f, 2000000.0f};
                float out[2] = {0.0f};
                
                vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
                
                assert(out[0] == 1000000.0f*1000000.0f + 2000000.0f*2000000.0f);
                assert(out[1] == 3000000.0f*1000000.0f + 4000000.0f*2000000.0f);
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }