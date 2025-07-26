// Optimized code(id = 3): 

void vectorMatrixMult(long int totalPixels, int availablePixels, int outPixelOffset, float* matrix, float* vector, float* out) {
    for (long int i = 0; i < availablePixels; ++i) {
        float sum = 0.0;
        for (long int j = 0; j < totalPixels; ++j) {
            sum += matrix[i * totalPixels + j] * vector[j];
        }
        out[i + outPixelOffset] = sum;
    }
}