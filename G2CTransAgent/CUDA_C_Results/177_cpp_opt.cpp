// Optimized code(id = 177): 

void sum_array_overlap(int* a, int* b, int* c, int N) {
            for (int gid = 0; gid < N; ++gid) {
                c[gid] = a[gid] + b[gid];
            }
        }