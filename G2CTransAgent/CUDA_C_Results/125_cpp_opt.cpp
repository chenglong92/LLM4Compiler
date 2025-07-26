// Optimized code(id = 125): 

#include <cmath>

        void doubleArrayElementwiseSquare(double* d_in, double* d_out, int length) {
            for (int tid = 0; tid < length; ++tid) {
                d_out[tid] = pow(d_in[tid], 2);
            }
        }