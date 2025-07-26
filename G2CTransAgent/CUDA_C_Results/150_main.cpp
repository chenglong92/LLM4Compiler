// original code(id = 150): 
 /*
__global__ void histogrammPrimitive ( unsigned int * histogrammVector , unsigned char * grayImage , int rows , int columns ) { int column = blockIdx . x * blockDim . x + threadIdx . x ; int row = blockIdx . y * blockDim . y + threadIdx . y ; int offset = ( column ) + ( columns * row ) ; if ( ( column < columns ) && ( row < rows ) ) { unsigned char grayValue = grayImage [ offset ] ; atomicAdd ( & ( histogrammVector [ grayValue ] ) , 1 ) ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstring>

void histogrammPrimitive(unsigned int* histogrammVector, unsigned char* grayImage, int rows, int columns);

int main() {
    // Test case 1: Normal case with small image
    {
        unsigned int histogram[256] = {0};
        unsigned char image[] = {10, 20, 30, 40, 50, 60};
        int rows = 2;
        int columns = 3;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        assert(histogram[10] == 1);
        assert(histogram[20] == 1);
        assert(histogram[30] == 1);
        assert(histogram[40] == 1);
        assert(histogram[50] == 1);
        assert(histogram[60] == 1);
        for (int i = 0; i < 256; ++i) {
            if (i != 10 && i != 20 && i != 30 && i != 40 && i != 50 && i != 60) {
                assert(histogram[i] == 0);
            }
        }
    }

    // Test case 2: Empty image (0 rows)
    {
        unsigned int histogram[256] = {0};
        unsigned char image[] = {};
        int rows = 0;
        int columns = 0;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        for (int i = 0; i < 256; ++i) {
            assert(histogram[i] == 0);
        }
    }

    // Test case 3: Single pixel image
    {
        unsigned int histogram[256] = {0};
        unsigned char image[] = {128};
        int rows = 1;
        int columns = 1;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        assert(histogram[128] == 1);
        for (int i = 0; i < 256; ++i) {
            if (i != 128) {
                assert(histogram[i] == 0);
            }
        }
    }

    // Test case 4: All pixels same value
    {
        unsigned int histogram[256] = {0};
        unsigned char image[100];
        memset(image, 42, sizeof(image));
        int rows = 10;
        int columns = 10;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        assert(histogram[42] == 100);
        for (int i = 0; i < 256; ++i) {
            if (i != 42) {
                assert(histogram[i] == 0);
            }
        }
    }

    // Test case 5: Large image with random values
    {
        unsigned int histogram[256] = {0};
        unsigned char image[10000];
        for (int i = 0; i < 10000; ++i) {
            image[i] = i % 256;
        }
        int rows = 100;
        int columns = 100;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        for (int i = 0; i < 256; ++i) {
            int expected = (i < 10000 % 256) ? (10000 / 256 + 1) : (10000 / 256);
            assert(histogram[i] == expected);
        }
    }

    // Test case 6: Edge case with maximum gray value (255)
    {
        unsigned int histogram[256] = {0};
        unsigned char image[] = {255, 255, 255, 255};
        int rows = 2;
        int columns = 2;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        assert(histogram[255] == 4);
        for (int i = 0; i < 255; ++i) {
            assert(histogram[i] == 0);
        }
    }

    // Test case 7: Edge case with minimum gray value (0)
    {
        unsigned int histogram[256] = {0};
        unsigned char image[] = {0, 0, 0, 0};
        int rows = 2;
        int columns = 2;
        
        histogrammPrimitive(histogram, image, rows, columns);
        
        assert(histogram[0] == 4);
        for (int i = 1; i < 256; ++i) {
            assert(histogram[i] == 0);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}