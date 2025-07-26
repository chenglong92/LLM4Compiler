// Optimized code(id = 150): 

void histogrammPrimitive(unsigned int* histogrammVector, unsigned char* grayImage, int rows, int columns) {
            for (int row = 0; row < rows; ++row) {
                for (int column = 0; column < columns; ++column) {
                    int offset = column + columns * row;
                    unsigned char grayValue = grayImage[offset];
                    histogrammVector[grayValue]++;
                }
            }
        }