// Optimized code(id = 32): 

void PSIfill(float* array, int conv_length, int maxThreads) {
    for (int i = 0; i < maxThreads; ++i) {
        array[i] = array[i % conv_length];
    }
}