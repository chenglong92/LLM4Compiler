// Optimized code(id = 128): 

void expandScoreFactors(const float* input, float* output, int dims, int clsNum) {
            for (int tid = 0; tid < dims; ++tid) {
                int k = tid / clsNum;
                output[tid] = input[k];
            }
        }