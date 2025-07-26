// Optimized code(id = 93): 

void matDiagAddInplace(double* mat, double alpha, int dim) {
            for (int i = 0; i < dim; ++i) {
                mat[i * dim + i] += alpha;
            }
        }