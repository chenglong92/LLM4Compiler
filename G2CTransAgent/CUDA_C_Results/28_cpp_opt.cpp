// Optimized code(id = 28): 

void dotKernel(float* c, float* a, float* b, int num_elements) {
    for (int t_id = 0; t_id < num_elements; ++t_id) {
        c[t_id] = a[t_id] * b[t_id];
    }
}