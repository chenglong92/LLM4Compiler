// Optimized code(id = 97): 

void addMatrixCPU(float* a, float* b, float* c, int N) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    int idx = i * N + j;
                    a[idx] = b[idx] + c[idx];
                }
            }
        }