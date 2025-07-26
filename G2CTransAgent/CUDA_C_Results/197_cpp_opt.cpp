// Optimized code(id = 197): 

void doubleArrayVectorElementwiseMultiply(double* d_in_a, double* d_in_b, double* d_out, int length) {
    for (int i = 0; i < length; ++i) {
        d_out[i] = d_in_a[i] * d_in_b[i];
    }
}