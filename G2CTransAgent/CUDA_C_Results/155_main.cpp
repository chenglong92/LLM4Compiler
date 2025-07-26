// original code(id = 155): 
 /*
__global__ void castImageToGrayScale ( unsigned char * ucharImage , unsigned char * grayImage , int imageWidth , int imageHeight , int channels ) { int w = threadIdx . x + blockDim . x * blockIdx . x ; int h = threadIdx . y + blockDim . y * blockIdx . y ; int idx = imageWidth * h + w ; if ( w < imageWidth && h < imageHeight ) { unsigned char r = ucharImage [ idx * channels ] ; unsigned char g = ucharImage [ idx * channels + 1 ] ; unsigned char b = ucharImage [ idx * channels + 2 ] ; grayImage [ idx ] = ( unsigned char ) ( 0.21f * r + 0.71f * g + 0.07f * b ) ; } }
*/
// optimized code: 

#include <cassert>
#include <cstring>

void castImageToGrayScale(unsigned char* ucharImage, unsigned char* grayImage, int imageWidth, int imageHeight, int channels);

int main() {
    // Test case 1: 2x2 RGB image
    {
        unsigned char input[] = {255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 255};
        unsigned char output[4];
        unsigned char expected[] = {54, 182, 18, 255};
        castImageToGrayScale(input, output, 2, 2, 3);
        assert(memcmp(output, expected, sizeof(expected)) == 0);
    }

    // Test case 2: 1x1 RGB image
    {
        unsigned char input[] = {128, 128, 128};
        unsigned char output[1];
        unsigned char expected[] = {128};
        castImageToGrayScale(input, output, 1, 1, 3);
        assert(memcmp(output, expected, sizeof(expected)) == 0);
    }

    // Test case 3: 3x1 RGBA image (4 channels)
    {
        unsigned char input[] = {255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255};
        unsigned char output[3];
        unsigned char expected[] = {54, 182, 18};
        castImageToGrayScale(input, output, 3, 1, 4);
        assert(memcmp(output, expected, sizeof(expected)) == 0);
    }

    // Test case 4: Empty image (0x0)
    {
        unsigned char input[] = {};
        unsigned char output[] = {};
        castImageToGrayScale(input, output, 0, 0, 3);
        // No assertion needed as it shouldn't crash
    }

    // Test case 5: Large image (100x100)
    {
        const int size = 100 * 100;
        unsigned char* input = new unsigned char[size * 3];
        unsigned char* output = new unsigned char[size];
        
        // Fill with pattern
        for (int i = 0; i < size; ++i) {
            input[i * 3] = i % 256;
            input[i * 3 + 1] = (i + 85) % 256;
            input[i * 3 + 2] = (i + 170) % 256;
        }
        
        castImageToGrayScale(input, output, 100, 100, 3);
        
        // Check first, middle and last pixels
        assert(output[0] == static_cast<unsigned char>(0.21f * 0 + 0.71f * 85 + 0.07f * 170));
        assert(output[size/2] == static_cast<unsigned char>(0.21f * (size/2 % 256) + 0.71f * ((size/2 + 85) % 256) + 0.07f * ((size/2 + 170) % 256)));
        assert(output[size-1] == static_cast<unsigned char>(0.21f * 99 + 0.71f * 184 + 0.07f * 13));
        
        delete[] input;
        delete[] output;
    }

    // Test case 6: Minimum values
    {
        unsigned char input[] = {0, 0, 0};
        unsigned char output[1];
        unsigned char expected[] = {0};
        castImageToGrayScale(input, output, 1, 1, 3);
        assert(memcmp(output, expected, sizeof(expected)) == 0);
    }

    // Test case 7: Maximum values
    {
        unsigned char input[] = {255, 255, 255};
        unsigned char output[1];
        unsigned char expected[] = {255};
        castImageToGrayScale(input, output, 1, 1, 3);
        assert(memcmp(output, expected, sizeof(expected)) == 0);
    }

    return 0;
}