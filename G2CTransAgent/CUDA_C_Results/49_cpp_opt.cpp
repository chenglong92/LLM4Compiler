// Optimized code(id = 49): 

void saxpy_cpu(const int dim, float a, float* x, float* y) {
    for (int i = 0; i < dim; ++i) {
        y[i] = a * x[i] + y[i];
    }
}