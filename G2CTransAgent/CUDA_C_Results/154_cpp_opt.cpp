// Optimized code(id = 154): 

void incrementArrayOnDevice(float* a, int N) {
            for (int idx = 0; idx < N; ++idx) {
                a[idx] = a[idx] + 1.0f;
            }
        }