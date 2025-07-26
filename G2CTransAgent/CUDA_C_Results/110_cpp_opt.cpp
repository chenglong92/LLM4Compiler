// Optimized code(id = 110): 

void shiftIndices(long* vec_out, const long by, const long imageSize, const long N) {
    for (long idx = 0; idx < N; ++idx) {
        vec_out[idx] = (imageSize + ((idx - N / 2 + by) % imageSize)) % imageSize;
    }
}