// Optimized code(id = 7): 

void incKernel(int* g_out, int* g_in, int N, int inner_reps) {
            for (int idx = 0; idx < N; ++idx) {
                for (int i = 0; i < inner_reps; ++i) {
                    g_out[idx] = g_in[idx] + 1;
                }
            }
        }