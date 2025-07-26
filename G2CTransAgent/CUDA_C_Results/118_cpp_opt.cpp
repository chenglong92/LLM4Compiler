// Optimized code(id = 118): 

void gaussianPass(int patchSize, int dataSize, float* gaussFilter, float* data) {
            for (int i = 0; i < dataSize; ++i) {
                data[i] = gaussFilter[i % (patchSize * patchSize)] * data[i];
            }
        }