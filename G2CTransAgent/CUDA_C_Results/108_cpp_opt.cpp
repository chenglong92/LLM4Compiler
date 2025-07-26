// Optimized code(id = 108): 

void dmul_Scalar_matrix(double* a, double value, double* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] * value;
    }
}