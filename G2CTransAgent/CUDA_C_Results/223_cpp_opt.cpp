// Optimized code(id = 223): 

void resetIndices(long* vec_out, const long N) {
    for (long idx = 0; idx < N; ++idx) {
        vec_out[idx] = idx;
    }
}