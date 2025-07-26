// Optimized code(id = 64): 

void saxpy_cpu(float* vecY, float* vecX, float alpha, int n) {
    for (int i = 0; i < n; i++) {
        vecY[i] = alpha * vecX[i] + vecY[i];
    }
}