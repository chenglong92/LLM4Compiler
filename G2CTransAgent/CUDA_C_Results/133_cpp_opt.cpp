// Optimized code(id = 133): 

void setIndexYolov3(int* input, int dims, int batchSize) {
            for (int tid = 0; tid < dims; ++tid) {
                for (int i = 0; i < batchSize; ++i) {
                    input[i * dims + tid] = tid;
                }
            }
        }