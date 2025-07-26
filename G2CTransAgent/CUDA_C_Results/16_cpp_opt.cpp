// Optimized code(id = 16): 

void upsweep_scan(int twod, int N, int* output) {
            int twod1 = twod * 2;
            int num_threads = (N + twod1 - 1) / twod1; // Calculate the number of threads needed
            for (int i = 0; i < num_threads; ++i) {
                int idx = i * twod1;
                if (idx + twod1 - 1 < N) {
                    output[idx + twod1 - 1] += output[idx + twod - 1];
                }
            }
        }