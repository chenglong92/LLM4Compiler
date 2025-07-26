// original code(id = 172): 
 /*
__global__ void equalization ( float * cdf , float * mincdf , unsigned char * ucharImage , int imageWidth , int imageHeight , int channels , int pixelSize ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx < pixelSize ) { unsigned char val = ucharImage [ idx ] ; float data = 255 * ( cdf [ val ] - mincdf [ 0 ] ) / ( 1 - mincdf [ 0 ] ) ; if ( data < 0.0f ) data = 0.0f ; else if ( data > 255.0f ) data = 255.0f ; ucharImage [ idx ] = ( unsigned char ) data ; } }
*/
// optimized code: 

#include <cassert>
#include <cstring>

void equalization(float* cdf, float* mincdf, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize);

int main() {
    // Test case 1: Normal case with values within range
    {
        float cdf[] = {0.1f, 0.3f, 0.6f, 1.0f};
        float mincdf[] = {0.1f};
        unsigned char image[] = {0, 1, 2, 3};
        int width = 2;
        int height = 2;
        int channels = 1;
        int pixelSize = 4;
        
        unsigned char expected[] = {0, 51, 153, 255};
        equalization(cdf, mincdf, image, width, height, channels, pixelSize);
        
        for (int i = 0; i < pixelSize; ++i) {
            assert(image[i] == expected[i]);
        }
    }

    // Test case 2: Values that would result in negative data (clamped to 0)
    {
        float cdf[] = {0.0f, 0.1f, 0.2f, 0.3f};
        float mincdf[] = {0.5f};
        unsigned char image[] = {0, 1, 2, 3};
        int width = 2;
        int height = 2;
        int channels = 1;
        int pixelSize = 4;
        
        unsigned char expected[] = {0, 0, 0, 0};
        equalization(cdf, mincdf, image, width, height, channels, pixelSize);
        
        for (int i = 0; i < pixelSize; ++i) {
            assert(image[i] == expected[i]);
        }
    }

    // Test case 3: Values that would result in data > 255 (clamped to 255)
    {
        float cdf[] = {0.9f, 0.95f, 0.99f, 1.0f};
        float mincdf[] = {0.0f};
        unsigned char image[] = {0, 1, 2, 3};
        int width = 2;
        int height = 2;
        int channels = 1;
        int pixelSize = 4;
        
        unsigned char expected[] = {255, 255, 255, 255};
        equalization(cdf, mincdf, image, width, height, channels, pixelSize);
        
        for (int i = 0; i < pixelSize; ++i) {
            assert(image[i] == expected[i]);
        }
    }

    // Test case 4: Single pixel case
    {
        float cdf[] = {0.0f, 0.5f, 1.0f};
        float mincdf[] = {0.0f};
        unsigned char image[] = {1};
        int width = 1;
        int height = 1;
        int channels = 1;
        int pixelSize = 1;
        
        unsigned char expected[] = {127};
        equalization(cdf, mincdf, image, width, height, channels, pixelSize);
        
        assert(image[0] == expected[0]);
    }

    // Test case 5: Multi-channel image
    {
        float cdf[] = {0.0f, 0.25f, 0.75f, 1.0f};
        float mincdf[] = {0.0f};
        unsigned char image[] = {0, 1, 2, 3, 0, 1, 2, 3};
        int width = 2;
        int height = 1;
        int channels = 4;
        int pixelSize = 8;
        
        unsigned char expected[] = {0, 63, 191, 255, 0, 63, 191, 255};
        equalization(cdf, mincdf, image, width, height, channels, pixelSize);
        
        for (int i = 0; i < pixelSize; ++i) {
            assert(image[i] == expected[i]);
        }
    }

    return 0;
}