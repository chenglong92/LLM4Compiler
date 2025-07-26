// Optimized code(id = 127): 

void Kernel_Transpose2d(float* dev_transposeArray, float* dev_array, const int r, const int c) {
            for (unsigned int i = 0; i < r; ++i) {
                for (unsigned int j = 0; j < c; ++j) {
                    int idx_array = i * c + j;
                    int idx_transposeArray = j * r + i;
                    dev_transposeArray[idx_transposeArray] = dev_array[idx_array];
                }
            }
        }