// Optimized code(id = 221): 

void compareDoubleArrayToThreshold(double* d_in, int* d_out, int length, double threshold) {
            for (int tid = 0; tid < length; ++tid) {
                double abs_val = d_in[tid] > 0 ? d_in[tid] : -d_in[tid];
                d_out[tid] = (abs_val < threshold);
            }
        }