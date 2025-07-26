// Optimized code(id = 38): 

#include <vector>

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