// Optimized code(id = 211): 

void kernelUpdateHead(int* head, int* d_idxs_out, int n) {
            for (int i = 0; i < n; ++i) {
                head[d_idxs_out[i]] = 1;
            }
        }