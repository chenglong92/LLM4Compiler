// Optimized code(id = 22): 

void zeroIndices(long* vec_out, const long N) {
            for (long idx = 0; idx < N; ++idx) {
                vec_out[idx] = vec_out[idx] - vec_out[0];
            }
        }