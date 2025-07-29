// Optimized code(id = 2): 

void boundaryCorrectIndexes(int* d_in, int* d_out, int length, int N) {
            for (int tid = 0; tid < length; ++tid) {
                if (d_in[tid] > N) {
                    d_out[tid] = N;
                } else {
                    d_out[tid] = d_in[tid];
                }
            }
        }