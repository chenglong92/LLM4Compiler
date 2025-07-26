// Optimized code(id = 43): 

void cpu_add(float* c, float* a, float* b, int n) {
    for (int j = 0; j < n; ++j) {
        c[j] = a[j] + b[j];
    }
}