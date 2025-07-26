// Optimized code(id = 73): 

void mul_kernel(int N, float* X, int INCX, float* Y, int INCY) {
            for (int i = 0; i < N; ++i) {
                Y[i * INCY] *= X[i * INCX];
            }
        }