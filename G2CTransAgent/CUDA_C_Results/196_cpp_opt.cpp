// Optimized code(id = 196): 

void matVecRowSub(const double* mat, const double* vec, double* buf, int m, int n) {
    for (int index = 0; index < m * n; ++index) {
        int i = index / n;
        int j = index % n;
        buf[i * n + j] = mat[i * n + j] - vec[j];
    }
}