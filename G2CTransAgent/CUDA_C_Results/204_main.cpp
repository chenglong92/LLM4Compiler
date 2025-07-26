// original code(id = 204): 
 /*
__global__ void castImageToUchar ( float * deviceInputImageData , unsigned char * ucharImage , int imageWidth , int imageHeight , int channels , int pixelSize ) { int w = threadIdx . x + blockDim . x * blockIdx . x ; if ( w < pixelSize ) ucharImage [ w ] = ( unsigned char ) ( 255 * deviceInputImageData [ w ] ) ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void castImageToUchar(float* deviceInputImageData, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize) {
    for (int w = 0; w < pixelSize; ++w) {
        ucharImage[w] = (unsigned char)(255 * deviceInputImageData[w]);
    }
}

int main() {
    // Test case 1: Single channel image with small dimensions
    {
        const int width = 2;
        const int height = 2;
        const int channels = 1;
        const int pixelSize = width * height * channels;
        
        float inputImage[pixelSize] = {0.0f, 0.5f, 1.0f, 0.25f};
        unsigned char outputImage[pixelSize] = {0};
        
        castImageToUchar(inputImage, outputImage, width, height, channels, pixelSize);
        
        assert(outputImage[0] == 0);
        assert(outputImage[1] == 127);
        assert(outputImage[2] == 255);
        assert(outputImage[3] == 63);
    }

    // Test case 2: Multi-channel image (RGB)
    {
        const int width = 1;
        const int height = 1;
        const int channels = 3;
        const int pixelSize = width * height * channels;
        
        float inputImage[pixelSize] = {0.0f, 0.33f, 0.66f};
        unsigned char outputImage[pixelSize] = {0};
        
        castImageToUchar(inputImage, outputImage, width, height, channels, pixelSize);
        
        assert(outputImage[0] == 0);
        assert(outputImage[1] == 84);
        assert(outputImage[2] == 168);
    }

    // Test case 3: Edge case - all zeros
    {
        const int width = 3;
        const int height = 1;
        const int channels = 1;
        const int pixelSize = width * height * channels;
        
        float inputImage[pixelSize] = {0.0f, 0.0f, 0.0f};
        unsigned char outputImage[pixelSize] = {0};
        
        castImageToUchar(inputImage, outputImage, width, height, channels, pixelSize);
        
        assert(outputImage[0] == 0);
        assert(outputImage[1] == 0);
        assert(outputImage[2] == 0);
    }

    // Test case 4: Edge case - all ones (max value)
    {
        const int width = 1;
        const int height = 2;
        const int channels = 1;
        const int pixelSize = width * height * channels;
        
        float inputImage[pixelSize] = {1.0f, 1.0f};
        unsigned char outputImage[pixelSize] = {0};
        
        castImageToUchar(inputImage, outputImage, width, height, channels, pixelSize);
        
        assert(outputImage[0] == 255);
        assert(outputImage[1] == 255);
    }

    // Test case 5: Large image dimensions
    {
        const int width = 100;
        const int height = 100;
        const int channels = 4;
        const int pixelSize = width * height * channels;
        
        float* inputImage = new float[pixelSize];
        unsigned char* outputImage = new unsigned char[pixelSize];
        
        for (int i = 0; i < pixelSize; ++i) {
            inputImage[i] = 0.5f;
        }
        
        castImageToUchar(inputImage, outputImage, width, height, channels, pixelSize);
        
        for (int i = 0; i < pixelSize; ++i) {
            assert(outputImage[i] == 127);
        }
        
        delete[] inputImage;
        delete[] outputImage;
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}