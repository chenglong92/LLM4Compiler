// Optimized code(id = 139): 

#include <cmath>
        #include <algorithm>

        void Kernel_Softmax_seg(float* dev_x, const int c, const int size) {
            int N = size;
            for (int i = 0; i < N; ++i) {
                float temp = 0.0f;
                for (int j = 0; j < c; ++j) {
                    temp = std::max(dev_x[j * size + i], temp);
                }
                for (int j = 0; j < c; ++j) {
                    dev_x[j * size + i] = expf(dev_x[j * size + i] - temp);
                }
                temp = 0.0f;
                for (int j = 0; j < c; ++j) {
                    temp += dev_x[j * size + i];
                }
                for (int j = 0; j < c; ++j) {
                    dev_x[j * size + i] /= temp;
                }
            }
        }