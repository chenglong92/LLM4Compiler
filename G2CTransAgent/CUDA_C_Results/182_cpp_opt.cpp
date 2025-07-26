// Optimized code(id = 182): 

void update_clusters(int n, int k, double* Cx, double* Cy, double* Cx_sum, double* Cy_sum, int* Csize) {
            for (int index = 0; index < k; ++index) {
                if (Csize[index]) {
                    Cx[index] = Cx_sum[index] / Csize[index];
                    Cy[index] = Cy_sum[index] / Csize[index];
                }
            }
        }