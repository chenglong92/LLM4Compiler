// Optimized code(id = 25): 

void subtract_matrix(double* a, double* b, double* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] - b[idx];
    }
}