// Optimized code(id = 192): 

void add_kernel(int N, float ALPHA, float* X, int INCX) {
    for (int i = 0; i < N; ++i) {
        X[i * INCX] += ALPHA;
    }
}