// Optimized code(id = 26): 

void test(float* input, const int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (tid == 0) {
            input[tid] = 0;
        }
    }
}