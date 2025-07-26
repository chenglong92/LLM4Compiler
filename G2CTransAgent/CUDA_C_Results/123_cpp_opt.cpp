// Optimized code(id = 123): 

void saxpy_cpu(float* x, float* y, float alpha, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = alpha * x[i] + y[i];
    }
}