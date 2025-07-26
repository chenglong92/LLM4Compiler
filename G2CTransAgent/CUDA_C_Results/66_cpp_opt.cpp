// Optimized code(id = 66): 

void matVecRowSubInplace(double* mat, const double* vec, int m, int n) {
    for (int index = 0; index < m * n; ++index) {
        int i = index / n;
        int j = index % n;
        mat[i * n + j] -= vec[j];
    }
}