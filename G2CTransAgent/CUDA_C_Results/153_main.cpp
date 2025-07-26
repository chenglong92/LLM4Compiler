// original code(id = 153): 
 /*
__global__ void castImageTofloat ( float * deviceOutputImageData , unsigned char * ucharImage , int imageWidth , int imageHeight , int channels , int pixelSize ) { int w = threadIdx . x + blockDim . x * blockIdx . x ; if ( w < pixelSize ) deviceOutputImageData [ w ] = ( float ) ( ucharImage [ w ] / 255.0 ) ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void castImageTofloat(float* deviceOutputImageData, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize) {
            for (int w = 0; w < pixelSize; ++w) {
                deviceOutputImageData[w] = static_cast<float>(ucharImage[w] / 255.0f);
            }
        }

        void testCastImageToFloat() {
            // Test case 1: Basic functionality with a simple 2x2 RGB image
            {
                const int width = 2;
                const int height = 2;
                const int channels = 3;
                const int pixelSize = width * height * channels;
                
                unsigned char inputImage[pixelSize] = {
                    0, 64, 128,    // Pixel 0
                    255, 32, 96,   // Pixel 1
                    16, 200, 240,  // Pixel 2
                    128, 128, 128  // Pixel 3
                };
                
                float outputImage[pixelSize];
                
                castImageTofloat(outputImage, inputImage, width, height, channels, pixelSize);
                
                assert(outputImage[0] == 0.0f / 255.0f);
                assert(outputImage[1] == 64.0f / 255.0f);
                assert(outputImage[2] == 128.0f / 255.0f);
                assert(outputImage[3] == 255.0f / 255.0f);
                assert(outputImage[4] == 32.0f / 255.0f);
                assert(outputImage[5] == 96.0f / 255.0f);
                assert(outputImage[6] == 16.0f / 255.0f);
                assert(outputImage[7] == 200.0f / 255.0f);
                assert(outputImage[8] == 240.0f / 255.0f);
                assert(outputImage[9] == 128.0f / 255.0f);
                assert(outputImage[10] == 128.0f / 255.0f);
                assert(outputImage[11] == 128.0f / 255.0f);
            }
            
            // Test case 2: Single channel image
            {
                const int width = 3;
                const int height = 1;
                const int channels = 1;
                const int pixelSize = width * height * channels;
                
                unsigned char inputImage[pixelSize] = {0, 127, 255};
                float outputImage[pixelSize];
                
                castImageTofloat(outputImage, inputImage, width, height, channels, pixelSize);
                
                assert(outputImage[0] == 0.0f / 255.0f);
                assert(outputImage[1] == 127.0f / 255.0f);
                assert(outputImage[2] == 255.0f / 255.0f);
            }
            
            // Test case 3: Edge cases (min and max values)
            {
                const int width = 2;
                const int height = 1;
                const int channels = 1;
                const int pixelSize = width * height * channels;
                
                unsigned char inputImage[pixelSize] = {0, 255};
                float outputImage[pixelSize];
                
                castImageTofloat(outputImage, inputImage, width, height, channels, pixelSize);
                
                assert(outputImage[0] == 0.0f / 255.0f);
                assert(outputImage[1] == 255.0f / 255.0f);
            }
            
            // Test case 4: Empty image
            {
                const int width = 0;
                const int height = 0;
                const int channels = 3;
                const int pixelSize = 0;
                
                unsigned char* inputImage = nullptr;
                float* outputImage = nullptr;
                
                castImageTofloat(outputImage, inputImage, width, height, channels, pixelSize);
                // No assertion needed, just checking it doesn't crash
            }
            
            // Test case 5: Different image dimensions
            {
                const int width = 1;
                const int height = 4;
                const int channels = 4;
                const int pixelSize = width * height * channels;
                
                unsigned char inputImage[pixelSize] = {
                    0, 0, 0, 0,
                    64, 64, 64, 64,
                    128, 128, 128, 128,
                    255, 255, 255, 255
                };
                
                float outputImage[pixelSize];
                
                castImageTofloat(outputImage, inputImage, width, height, channels, pixelSize);
                
                for (int i = 0; i < pixelSize; i += 4) {
                    assert(outputImage[i] == inputImage[i] / 255.0f);
                    assert(outputImage[i+1] == inputImage[i+1] / 255.0f);
                    assert(outputImage[i+2] == inputImage[i+2] / 255.0f);
                    assert(outputImage[i+3] == inputImage[i+3] / 255.0f);
                }
            }
            
            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            testCastImageToFloat();
            return 0;
        }