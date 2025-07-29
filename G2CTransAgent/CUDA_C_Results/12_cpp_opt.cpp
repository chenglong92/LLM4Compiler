// Optimized code(id = 12): 

void testInt1(const int* input, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                int sum = 0;
                for (int i = 0; i < 3000 * 4; ++i) {
                    if (input[i] == 0) {
                        sum++;
                    }
                }
                // sum is unused in original code
            }
        }