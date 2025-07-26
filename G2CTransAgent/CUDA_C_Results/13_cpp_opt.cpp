// Optimized code(id = 13): 

void copy_swap(float* f_in, float* f_target, const int L_x) {
            for (int k_x = 0; k_x < L_x; ++k_x) {
                float tempval = f_in[k_x];
                f_in[k_x] = f_target[k_x];
                f_target[k_x] = tempval;
            }
        }