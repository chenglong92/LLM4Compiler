// Optimized code(id = 207): 

#include <algorithm>

void clamp_kernel(int N, float* X, int INCX, float clamp_min, float clamp_max) {
    for (int i = 0; i < N; ++i) {
        X[i * INCX] = std::min(clamp_max, std::max(clamp_min, X[i * INCX]));
    }
}