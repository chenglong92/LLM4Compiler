// Optimized code(id = 76): 

void cpu_matrix_mul(int* a, int* b, int* c, int N) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            int sum = 0;
            for (int i = 0; i < N; ++i) {
                sum += a[row * N + i] * b[i * N + col];
            }
            c[row * N + col] = sum;
        }
    }
}