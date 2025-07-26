// Optimized code(id = 184): 

void vectorMatrixMult(long int totalPixels, float* matrix, float* vector, float* out) {
    for (long int i = 0; i < totalPixels; ++i) {
        float sum = 0.0;
        for (long int j = 0; j < totalPixels; ++j) {
            sum += matrix[i * totalPixels + j] * vector[j];
        }
        out[i] = sum;
    }
}