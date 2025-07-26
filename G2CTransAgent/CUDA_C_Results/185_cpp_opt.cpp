// Optimized code(id = 185): 

void boxesScale(const float* input, float* output, int dims, float scale0, float scale1, float scale2, float scale3) {
    for (int tid = 0; tid < dims; ++tid) {
        output[tid * 4] = input[tid * 4] / scale0;
        output[tid * 4 + 1] = input[tid * 4 + 1] / scale1;
        output[tid * 4 + 2] = input[tid * 4 + 2] / scale2;
        output[tid * 4 + 3] = input[tid * 4 + 3] / scale3;
    }
}