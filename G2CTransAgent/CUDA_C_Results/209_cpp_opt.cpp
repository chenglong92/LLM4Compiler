// Optimized code(id = 209): 

void add_matrix(float* a, float* b, float* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] + b[idx];
    }
}