// Optimized code(id = 51): 

void compute_b_minus_Rx(double* out, double* x, double* b, double* cotans, int* neighbors, int meshStride, int n) {
            for (int i = 0; i < n; ++i) {
                out[i] = b[i];
                for (int iN = 0; iN < meshStride; ++iN) {
                    int neighbor = neighbors[i * meshStride + iN];
                    double weight = cotans[i * meshStride + iN];
                    out[i] -= weight * x[neighbor];
                }
            }
        }