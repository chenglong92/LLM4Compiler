// Optimized code(id = 142): 

void test1(float* input, int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (input[tid * 4] != 0) {
            input[tid * 4] = 0;
        }
    }
}