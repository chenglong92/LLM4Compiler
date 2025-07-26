// original code(id = 38): 
 /*
__global__ void colorConvert ( unsigned char * grayImage , unsigned char * colorImage , int rows , int columns ) { int column = blockIdx . x * blockDim . x + threadIdx . x ; int row = blockIdx . y * blockDim . y + threadIdx . y ; if ( ( column < columns ) && ( row < rows ) ) { int offset = ( column ) + ( columns * row ) ; unsigned char grayValue = 0.07 * colorImage [ offset * 3 ] + 0.71 * colorImage [ offset * 3 + 1 ] + 0.21 * colorImage [ offset * 3 + 2 ] ; grayImage [ offset ] = grayValue ; } }
*/
// optimized code: 

#include <vector>
#include <cassert>
#include <iostream>
#include <cstring>

void colorConvert(unsigned char* grayImage, unsigned char* colorImage, int rows, int columns);

int main() {
    // Test case 1: Empty image (0 rows)
    {
        unsigned char grayImage[1] = {0};
        unsigned char colorImage[1] = {0};
        colorConvert(grayImage, colorImage, 0, 100);
        assert(grayImage[0] == 0); // Should remain unchanged
    }

    // Test case 2: Empty image (0 columns)
    {
        unsigned char grayImage[1] = {0};
        unsigned char colorImage[1] = {0};
        colorConvert(grayImage, colorImage, 100, 0);
        assert(grayImage[0] == 0); // Should remain unchanged
    }

    // Test case 3: Single pixel image
    {
        unsigned char grayImage[1] = {0};
        unsigned char colorImage[3] = {100, 150, 200};
        colorConvert(grayImage, colorImage, 1, 1);
        unsigned char expected = 0.07 * 100 + 0.71 * 150 + 0.21 * 200;
        assert(grayImage[0] == expected);
    }

    // Test case 4: 2x2 image
    {
        unsigned char grayImage[4] = {0};
        unsigned char colorImage[12] = {
            255, 0, 0,    // Red
            0, 255, 0,    // Green
            0, 0, 255,    // Blue
            255, 255, 255 // White
        };
        colorConvert(grayImage, colorImage, 2, 2);
        
        // Verify red pixel
        assert(grayImage[0] == static_cast<unsigned char>(0.07 * 255));
        // Verify green pixel
        assert(grayImage[1] == static_cast<unsigned char>(0.71 * 255));
        // Verify blue pixel
        assert(grayImage[2] == static_cast<unsigned char>(0.21 * 255));
        // Verify white pixel
        assert(grayImage[3] == static_cast<unsigned char>(0.07 * 255 + 0.71 * 255 + 0.21 * 255));
    }

    // Test case 5: Boundary condition (last pixel)
    {
        const int rows = 10;
        const int columns = 10;
        unsigned char grayImage[rows * columns] = {0};
        unsigned char colorImage[rows * columns * 3] = {0};
        
        // Set last pixel to known values
        int last_pixel_offset = (rows * columns - 1) * 3;
        colorImage[last_pixel_offset] = 100;
        colorImage[last_pixel_offset + 1] = 100;
        colorImage[last_pixel_offset + 2] = 100;
        
        colorConvert(grayImage, colorImage, rows, columns);
        
        unsigned char expected = 0.07 * 100 + 0.71 * 100 + 0.21 * 100;
        assert(grayImage[rows * columns - 1] == expected);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void colorConvert(unsigned char* grayImage, unsigned char* colorImage, int rows, int columns) {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (column < columns && row < rows) {
                int offset = column + (columns * row);
                unsigned char grayValue = 0.07 * colorImage[offset * 3] + 
                                         0.71 * colorImage[offset * 3 + 1] + 
                                         0.21 * colorImage[offset * 3 + 2];
                grayImage[offset] = grayValue;
            }
        }
    }
}