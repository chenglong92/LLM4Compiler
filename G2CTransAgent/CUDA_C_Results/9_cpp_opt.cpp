// Optimized code(id = 9): 

void doubleArrayScalarDivide(double* d_in, int* d_out, int length, double scalar) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = static_cast<int>(d_in[tid] / scalar);
    }
}