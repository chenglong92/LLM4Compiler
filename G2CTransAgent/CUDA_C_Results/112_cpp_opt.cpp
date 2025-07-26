// Optimized code(id = 112): 

void solveLowerKernel(const double* lower, const double* b, double* buf, int dim, int n) {
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < dim; ++i) {
                    double val = b[k * dim + i];
                    for (int j = 0; j < i; ++j) {
                        val -= lower[i * dim + j] * buf[k * dim + j];
                    }
                    buf[k * dim + i] = val / lower[i * dim + i];
                }
            }
        }