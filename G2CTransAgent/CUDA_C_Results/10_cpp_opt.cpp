// Optimized code(id = 10): 

void kernelMaximum(float* maxhd, float* maxvd, int start, int size) {
            for (int i = size >> 1; i > 0; i >>= 1) {
                for (int tx = start; tx < i; ++tx) {
                    if (maxhd[tx] < maxhd[tx + i]) {
                        maxhd[tx] = maxhd[tx + i];
                    }
                    if (maxvd[tx] < maxvd[tx + i]) {
                        maxvd[tx] = maxvd[tx + i];
                    }
                }
            }
        }