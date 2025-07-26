// Optimized code(id = 147): 

void doubleArrayScalarMultiply(double* d_in, double* d_out, int length, double scalar) {
            for (int i = 0; i < length; ++i) {
                d_out[i] = d_in[i] * scalar;
            }
        }