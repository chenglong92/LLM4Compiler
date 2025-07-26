// Optimized code(id = 23): 

void mul_Scalar_matrix(float* a, float value, float* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] * value;
    }
}