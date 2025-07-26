// Optimized code(id = 205): 

void inter_kernel(int NX, float* X, int NY, float* Y, int B, float* OUT) {
    for (int i = 0; i < (NX + NY) * B; ++i) {
        int b = i / (NX + NY);
        int j = i % (NX + NY);
        if (j < NX) {
            OUT[i] = X[b * NX + j];
        } else {
            OUT[i] = Y[b * NY + j - NX];
        }
    }
}