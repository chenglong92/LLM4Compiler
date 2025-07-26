// Optimized code(id = 84): 

void resizedClsScore(const float* score, const float* score_factors, float* output, int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (score[tid] == (-1)) {
            output[tid] = -1;
        } else {
            output[tid] = score[tid] * score_factors[tid];
        }
    }
}