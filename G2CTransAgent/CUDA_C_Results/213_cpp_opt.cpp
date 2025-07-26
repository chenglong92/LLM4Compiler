// Optimized code(id = 213): 

#include <cmath>
        #include <algorithm>

        void kernel_softmax(float* x, int r, int c) {
            for (unsigned int i = 0; i < r; ++i) {
                float temp1 = 0.0f;
                float temp2 = 0.0f;
                
                // Find maximum value in the row
                for (int j = 0; j < c; ++j) {
                    temp1 = std::max(x[i * c + j], temp1);
                }
                
                // Compute exponentials and their sum
                for (int j = 0; j < c; ++j) {
                    x[i * c + j] = expf(x[i * c + j] - temp1);
                    temp2 += x[i * c + j];
                }
                
                // Normalize by the sum
                for (int j = 0; j < c; ++j) {
                    x[i * c + j] /= temp2;
                }
            }
        }