// Optimized code(id = 0): 

void naive_sgemm(float* C, float* A, float* B, long size) {
            for (long i = 0; i < size; ++i) {
                for (long j = 0; j < size; ++j) {
                    float val = 0.0;
                    for (long k = 0; k < size; ++k) {
                        val += A[i * size + k] * B[k * size + j];
                    }
                    C[i * size + j] += val;
                }
            }
        }