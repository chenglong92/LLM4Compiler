// Optimized code(id = 6): 

void Kernel_Sum_backward_opt2(float* db, float* sum, int r_sum, int c) {
            for (int j = 0; j < c; ++j) {
                float temp = 0;
                for (int i = 0; i < r_sum; ++i) {
                    temp += sum[i * c + j];
                }
                db[j] = temp;
            }
        }