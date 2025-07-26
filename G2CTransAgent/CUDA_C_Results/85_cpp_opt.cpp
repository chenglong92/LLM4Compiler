// Optimized code(id = 85): 

void gather_points_kernel(int b, int c, int n, int m, const float* points, const int* idx, float* out) {
    for (int i = 0; i < b; ++i) {
        for (int l = 0; l < c; ++l) {
            for (int j = 0; j < m; ++j) {
                int a = idx[i * m + j];
                out[(i * c + l) * m + j] = points[(i * c + l) * n + a];
            }
        }
    }
}