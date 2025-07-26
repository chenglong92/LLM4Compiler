// Optimized code(id = 115): 

void mathKernel1(float* c, int num_elements) {
            for (int tid = 0; tid < num_elements; ++tid) {
                float ia = 0.0f, ib = 0.0f;
                if (tid % 2 == 0) {
                    ia = 100.0f;
                } else {
                    ib = 200.0f;
                }
                c[tid] = ia + ib;
            }
        }