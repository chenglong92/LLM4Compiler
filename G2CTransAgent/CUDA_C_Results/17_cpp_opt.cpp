// Optimized code(id = 17): 

void upsweep_scan(int twod, int N, int* output) {
            int twod1 = twod * 2;
            // Calculate the maximum number of threads that would have been launched in CUDA
            // Assuming blockDim.x = 256 (common value) and enough blocks to cover N
            const int blockDim = 256;
            int gridDim = (N + twod1 - 1) / (blockDim * twod1) + 1;
            
            for (int blockIdx = 0; blockIdx < gridDim; ++blockIdx) {
                for (int threadIdx = 0; threadIdx < blockDim; ++threadIdx) {
                    int idx = (blockIdx * blockDim + threadIdx) * twod1;
                    if (idx + twod1 - 1 < N) {
                        output[idx + twod1 - 1] += output[idx + twod - 1];
                    }
                }
            }
        }