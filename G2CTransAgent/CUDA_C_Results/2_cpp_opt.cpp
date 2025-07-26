// Optimized code(id = 2): 

void set_valid_mask(const float* score, float score_thr, int* valid_mask, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (score[tid] > score_thr) {
                    valid_mask[tid] = 1;
                } else {
                    valid_mask[tid] = 0;
                }
            }
        }