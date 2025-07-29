// Optimized code(id = 4): 

#include <iostream>

void vectorMatrixMult(long int totalPixels, int availablePixels, int outPixelOffset, float* matrix, float* vector, float* out) {
    for (long int i = 0; i < availablePixels; ++i) {
        float sum = 0.0;
        for (long int j = 0; j < totalPixels; ++j) {
            sum += matrix[i * totalPixels + j] * vector[j];
        }
        out[i + outPixelOffset] = sum;
    }
}

// Example usage (commented out):
/*
int main() {
    const long int totalPixels = 100;
    const int availablePixels = 50;
    const int outPixelOffset = 0;
    
    float* matrix = new float[availablePixels * totalPixels];
    float* vector = new float[totalPixels];
    float* out = new float[availablePixels + outPixelOffset];
    
    // Initialize matrix and vector with some values
    for (long int i = 0; i < availablePixels * totalPixels; ++i) {
        matrix[i] = static_cast<float>(i % 10) * 0.1f;
    }
    for (long int j = 0; j < totalPixels; ++j) {
        vector[j] = static_cast<float>(j % 5) * 0.2f;
    }
    
    vectorMatrixMult(totalPixels, availablePixels, outPixelOffset, matrix, vector, out);
    
    // Clean up
    delete[] matrix;
    delete[] vector;
    delete[] out;
    
    return 0;
}
*/