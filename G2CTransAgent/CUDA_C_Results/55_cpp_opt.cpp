// Optimized code(id = 55): 

void cpu_add(float* c, float* a, float* b, int n) {
    for (int k = 0; k < n; ++k) {
        c[k] = a[k] + b[k];
    }
}