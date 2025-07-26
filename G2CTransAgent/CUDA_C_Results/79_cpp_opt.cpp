// Optimized code(id = 79): 

void mxm_1d(double* a, const int m, double* b, const int n, double* c, const int p) {
            for (int i = 0; i < m; ++i) {
                for (int k = 0; k < p; ++k) {
                    double s = 0.0;
                    for (int j = 0; j < n; ++j) {
                        s += a[j * m + i] * b[k * n + j];
                    }
                    c[k * m + i] = s;
                }
            }
        }