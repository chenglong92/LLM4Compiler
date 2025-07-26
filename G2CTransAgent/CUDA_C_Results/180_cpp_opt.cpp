// Optimized code(id = 180): 

void doubleArrayVectorSubtract(double* d_in_a, double* d_in_b, double* d_out, int length) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in_a[tid] - d_in_b[tid];
    }
}