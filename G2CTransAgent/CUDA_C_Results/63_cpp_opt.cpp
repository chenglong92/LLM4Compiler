// Optimized code(id = 63): 

void devidecount(long Xsize, long Ysize, long Zsize, double* pint, int* pcount) {
            int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
            long total_elements = n * n;
            for (long tid = 0; tid < total_elements; ++tid) {
                if (pcount[tid] > 1) {
                    pint[tid] /= pcount[tid];
                }
            }
        }