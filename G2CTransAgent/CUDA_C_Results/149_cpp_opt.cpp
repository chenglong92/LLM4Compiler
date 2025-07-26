// Optimized code(id = 149): 

void vectorAdd(const float* A, const float* B, float* C, int numElements) {
    for (int i = 0; i < numElements; ++i) {
        C[i] = A[i] + B[i];
    }
}