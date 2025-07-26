// Optimized code(id = 67): 

#include <algorithm>
        #include <cmath>

        void fabsf_clamp_kernel(int N, float* X, int INCX, float clamp_min, float clamp_max) {
            for (int i = 0; i < N; ++i) {
                if (X[i * INCX] >= 0) {
                    X[i * INCX] = std::min(clamp_max, std::max(clamp_min, X[i * INCX]));
                } else {
                    X[i * INCX] = std::min(-clamp_min, std::max(-clamp_max, X[i * INCX]));
                }
            }
        }