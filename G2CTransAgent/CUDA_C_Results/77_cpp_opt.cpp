// Optimized code(id = 77): 

#include <cmath>

        void pow_kernel(int N, float ALPHA, float* X, int INCX, float* Y, int INCY) {
            for (int i = 0; i < N; ++i) {
                Y[i * INCY] = pow(X[i * INCX], ALPHA);
            }
        }