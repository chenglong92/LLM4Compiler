// Optimized code(id = 131): 

#include <iostream>

void deinter_kernel(int NX, float* X, int NY, float* Y, int B, float* OUT) {
    for (int i = 0; i < (NX + NY) * B; ++i) {
        int b = i / (NX + NY);
        int j = i % (NX + NY);
        if (j < NX) {
            if (X) X[b * NX + j] += OUT[i];
        } else {
            if (Y) Y[b * NY + (j - NX)] += OUT[i];
        }
    }
}

// Example usage (commented out)
/*
int main() {
    // Initialize parameters and arrays
    int NX = 10, NY = 5, B = 3;
    float *X = new float[NX * B];
    float *Y = new float[NY * B];
    float *OUT = new float[(NX + NY) * B];
    
    // Initialize arrays with some values
    for (int i = 0; i < NX * B; ++i) X[i] = 0.0f;
    for (int i = 0; i < NY * B; ++i) Y[i] = 0.0f;
    for (int i = 0; i < (NX + NY) * B; ++i) OUT[i] = 1.0f;
    
    // Call the function
    deinter_kernel(NX, X, NY, Y, B, OUT);
    
    // Clean up
    delete[] X;
    delete[] Y;
    delete[] OUT;
    
    return 0;
}
*/