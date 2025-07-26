// Optimized code(id = 171): 

void vectorAdd(double* a, double* b, double* c, int vector_size) {
    for (int tid = 0; tid < vector_size; ++tid) {
        c[tid] = a[tid] + b[tid];
    }
}