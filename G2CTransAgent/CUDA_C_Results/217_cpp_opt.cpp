// Optimized code(id = 217): 

void binarize_kernel(float* x, int n, float* binary) {
    for (int i = 0; i < n; ++i) {
        binary[i] = (x[i] >= 0) ? 1.0f : -1.0f;
    }
}