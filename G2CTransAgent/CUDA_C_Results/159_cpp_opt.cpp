// Optimized code(id = 159): 

void convoluteCPU(float* dData, float* hData, int height, int width, float* mask, int masksize) {
    int S = (masksize - 1) / 2;
    
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            float sum = 0.0f;
            int pixPos = row * width + col;
            dData[pixPos] = 0.0f;
            
            for (int maskrow = -S; maskrow <= S; ++maskrow) {
                for (int maskcol = -S; maskcol <= S; ++maskcol) {
                    int pixP = (row + maskrow) * width + (col + maskcol);
                    int maskP = (maskrow + S) * masksize + (maskcol + S);
                    
                    if (pixP >= 0 && pixP < height * width && maskP < masksize * masksize) {
                        sum += mask[maskP] * hData[pixP];
                    }
                }
            }
            
            dData[pixPos] = sum;
            if (dData[pixPos] < 0) {
                dData[pixPos] = 0;
            } else if (dData[pixPos] > 1) {
                dData[pixPos] = 1;
            }
        }
    }
}