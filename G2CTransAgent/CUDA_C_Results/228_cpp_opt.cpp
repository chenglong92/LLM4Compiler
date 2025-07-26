// Optimized code(id = 228): 

#include <cmath>

        void sigmoid_kernel(float* input, float* output, int size) {
            for (int tid = 0; tid < size; ++tid) {
                output[tid] = 1.0f / (1.0f + expf(-input[tid]));
            }
        }