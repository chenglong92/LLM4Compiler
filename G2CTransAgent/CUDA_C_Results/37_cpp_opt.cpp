// Optimized code(id = 37): 

void MulMatrixOnCPU(float* A, float* B, float* C, int nx, int ny) {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < nx; ++k) {
                sum += A[i * nx + k] * B[k * nx + j];
            }
            C[i * nx + j] = sum;
        }
    }
}