// Optimized code(id = 100): 

void mmul(const float* A, const float* B, float* C, int r1, int c1, int r2, int c2) {
    for (int idy = 0; idy < r1; ++idy) {
        for (int idx = 0; idx < c2; ++idx) {
            float temp = 0;
            for (int i = 0; i < c1; ++i) {
                temp += A[idy * c1 + i] * B[i * c2 + idx];
            }
            C[idy * c2 + idx] = temp;
        }
    }
}