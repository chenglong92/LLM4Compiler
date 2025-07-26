// Optimized code(id = 119): 

void getMeanImage(const double* images, double* meanImage, int imageNum, int pixelNum) {
            for (int col = 0; col < pixelNum; ++col) {
                meanImage[col] = 0.0;
                for (int row = 0; row < imageNum; ++row) {
                    meanImage[col] += images[row * pixelNum + col];
                }
                meanImage[col] /= imageNum;
            }
        }