// Optimized code(id = 232): 

void doubleArrayScalarAdd(double* d_in, double* d_out, int length, double scalar) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in[tid] + scalar;
    }
}