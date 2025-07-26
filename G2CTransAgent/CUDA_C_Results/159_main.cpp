// original code(id = 159): 
 /*
__global__ void convoluteGPU ( float * dData , float * hData , int height , int width , float * mask , int masksize ) { int row = threadIdx . x + blockIdx . x * blockDim . x ; int col = threadIdx . y + blockIdx . y * blockDim . y ; int S = ( masksize - 1 ) / 2 ; float sum = 0 ; int pixPos = row * width + col ; dData [ pixPos ] = 0.0 ; if ( row < height && col < width ) { for ( int maskrow = - S ; maskrow <= S ; maskrow ++ ) { for ( int maskcol = - S ; maskcol <= S ; maskcol ++ ) { int pixP = ( row + maskrow ) * width + ( col + maskcol ) ; int maskP = ( maskrow + S ) * masksize + ( maskcol + S ) ; if ( pixP < height * width && pixP > 0 && maskP < masksize * masksize ) { sum += mask [ maskP ] * hData [ pixP ] ; } } } dData [ pixPos ] = sum ; if ( dData [ pixPos ] < 0 ) { dData [ pixPos ] = 0 ; } else if ( dData [ pixPos ] > 1 ) { dData [ pixPos ] = 1 ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void convoluteCPU(float* dData, float* hData, int height, int width, float* mask, int masksize);

        int main() {
            // Test Case 1: Normal case with 3x3 mask and 5x5 image
            {
                const int height = 5;
                const int width = 5;
                const int masksize = 3;
                
                float hData[height * width] = {
                    0.1f, 0.2f, 0.3f, 0.4f, 0.5f,
                    0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
                    0.1f, 0.2f, 0.3f, 0.4f, 0.5f,
                    0.6f, 0.7f, 0.8f, 0.9f, 1.0f,
                    0.1f, 0.2f, 0.3f, 0.4f, 0.5f
                };
                
                float mask[masksize * masksize] = {
                    1.0f/9, 1.0f/9, 1.0f/9,
                    1.0f/9, 1.0f/9, 1.0f/9,
                    1.0f/9, 1.0f/9, 1.0f/9
                };
                
                float dData[height * width] = {0};
                
                convoluteCPU(dData, hData, height, width, mask, masksize);
                
                // Verify the output is within [0,1] range
                for (int i = 0; i < height * width; ++i) {
                    assert(dData[i] >= 0.0f && dData[i] <= 1.0f);
                }
            }
            
            // Test Case 2: Edge case with 1x1 mask (no convolution)
            {
                const int height = 3;
                const int width = 3;
                const int masksize = 1;
                
                float hData[height * width] = {
                    0.1f, 0.2f, 0.3f,
                    0.4f, 0.5f, 0.6f,
                    0.7f, 0.8f, 0.9f
                };
                
                float mask[masksize * masksize] = {1.0f};
                
                float dData[height * width] = {0};
                
                convoluteCPU(dData, hData, height, width, mask, masksize);
                
                // Verify output matches input (since mask is 1x1)
                for (int i = 0; i < height * width; ++i) {
                    assert(dData[i] == hData[i]);
                }
            }
            
            // Test Case 3: Edge case with mask larger than image (3x3 mask, 2x2 image)
            {
                const int height = 2;
                const int width = 2;
                const int masksize = 3;
                
                float hData[height * width] = {
                    0.5f, 0.5f,
                    0.5f, 0.5f
                };
                
                float mask[masksize * masksize] = {
                    0.1f, 0.1f, 0.1f,
                    0.1f, 0.1f, 0.1f,
                    0.1f, 0.1f, 0.1f
                };
                
                float dData[height * width] = {0};
                
                convoluteCPU(dData, hData, height, width, mask, masksize);
                
                // Verify the output is within [0,1] range
                for (int i = 0; i < height * width; ++i) {
                    assert(dData[i] >= 0.0f && dData[i] <= 1.0f);
                }
            }
            
            // Test Case 4: Abnormal case with empty image (0x0)
            {
                const int height = 0;
                const int width = 0;
                const int masksize = 3;
                
                float* hData = nullptr;
                float mask[masksize * masksize] = {
                    0.1f, 0.1f, 0.1f,
                    0.1f, 0.1f, 0.1f,
                    0.1f, 0.1f, 0.1f
                };
                
                float* dData = nullptr;
                
                // Should not crash
                convoluteCPU(dData, hData, height, width, mask, masksize);
            }
            
            // Test Case 5: Random data test with clamping verification
            {
                const int height = 10;
                const int width = 10;
                const int masksize = 5;
                
                float hData[height * width];
                float mask[masksize * masksize];
                
                // Initialize with random values
                std::srand(std::time(0));
                for (int i = 0; i < height * width; ++i) {
                    hData[i] = static_cast<float>(std::rand()) / RAND_MAX;
                }
                for (int i = 0; i < masksize * masksize; ++i) {
                    mask[i] = static_cast<float>(std::rand()) / RAND_MAX;
                }
                
                float dData[height * width] = {0};
                
                convoluteCPU(dData, hData, height, width, mask, masksize);
                
                // Verify the output is clamped to [0,1] range
                for (int i = 0; i < height * width; ++i) {
                    assert(dData[i] >= 0.0f && dData[i] <= 1.0f);
                }
            }
            
            std::cout << "All tests passed successfully!" << std::endl;
            
            return 0;
        }