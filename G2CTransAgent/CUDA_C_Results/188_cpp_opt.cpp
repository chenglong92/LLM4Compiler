// Optimized code(id = 188): 

void returnResult(const float* box, const float* score, const int* label, float* box_out, float* score_out, int* label_out, float score_thr, const int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (score[tid] < score_thr) {
                    score_out[tid] = 0;
                    box_out[tid * 4 + 0] = -1;
                    box_out[tid * 4 + 1] = -1;
                    box_out[tid * 4 + 2] = -1;
                    box_out[tid * 4 + 3] = -1;
                    label_out[tid] = -1;
                } else {
                    score_out[tid] = score[tid];
                    box_out[tid * 4 + 0] = box[tid * 4 + 0];
                    box_out[tid * 4 + 1] = box[tid * 4 + 1];
                    box_out[tid * 4 + 2] = box[tid * 4 + 2];
                    box_out[tid * 4 + 3] = box[tid * 4 + 3];
                    label_out[tid] = label[tid];
                }
            }
        }