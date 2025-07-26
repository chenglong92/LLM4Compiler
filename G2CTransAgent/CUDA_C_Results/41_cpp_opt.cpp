// Optimized code(id = 41): 

void memsetCudaInt(int* data, int val, int N) {
    for (unsigned int index = 0; index < N; ++index) {
        data[index] = val;
    }
}