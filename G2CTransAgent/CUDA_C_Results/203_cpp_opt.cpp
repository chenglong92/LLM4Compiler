// Optimized code(id = 203): 

void update_x(double* x, double* a, double* b, int n) {
    for (int i = 0; i < n; ++i) {
        x[i] = 2. / 3. * a[i] / b[i] + 1. / 3. * x[i];
    }
}