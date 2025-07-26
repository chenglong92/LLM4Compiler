// Optimized code(id = 148): 

void const_kernel(int N, float ALPHA, float* X, int INCX) {
            for (int i = 0; i < N; ++i) {
                X[i * INCX] = ALPHA;
            }
        }