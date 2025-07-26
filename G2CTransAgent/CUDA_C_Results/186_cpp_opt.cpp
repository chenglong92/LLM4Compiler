// Optimized code(id = 186): 

void doubleArraySign(double* d_in, double* d_out, int length) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = (0 < d_in[tid]) - (d_in[tid] < 0);
    }
}