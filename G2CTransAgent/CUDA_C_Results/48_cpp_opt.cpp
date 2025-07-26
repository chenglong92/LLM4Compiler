// Optimized code(id = 48): 

void VectorAdd(float* arrayA, float* arrayB, float* output, int size) {
    for (int idx = 0; idx < size; ++idx) {
        output[idx] = arrayA[idx] + arrayB[idx];
    }
}