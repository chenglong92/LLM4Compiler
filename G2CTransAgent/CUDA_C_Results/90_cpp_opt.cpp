// Optimized code(id = 90): 

void scale_dev(float* array, float scale, int N) {
    for (int idx = 0; idx < N; ++idx) {
        array[idx] *= scale;
    }
}