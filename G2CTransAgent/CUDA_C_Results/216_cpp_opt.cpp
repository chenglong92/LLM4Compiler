// Optimized code(id = 216): 

void clip_kernel(int N, float ALPHA, float* X, int INCX, float* Y, int INCY) {
    for (int i = 0; i < N; ++i) {
        float val = X[i * INCX];
        Y[i * INCY] = val > ALPHA ? val : 0;
    }
}