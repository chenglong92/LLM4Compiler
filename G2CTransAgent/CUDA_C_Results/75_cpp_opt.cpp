// Optimized code(id = 75): 

void mult_add_into_kernel(int n, float* a, float* b, float* c) {
    for (int i = 0; i < n; ++i) {
        c[i] += a[i] * b[i];
    }
}