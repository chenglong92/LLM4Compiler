// Optimized code(id = 164): 

void zero_centroid_vals(int k, double* Cx_sum, double* Cy_sum, int* Csize) {
            for (int index = 0; index < k; ++index) {
                Cx_sum[index] = 0;
                Cy_sum[index] = 0;
                Csize[index] = 0;
            }
        }