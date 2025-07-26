// Optimized code(id = 165): 

void kernel_sum_backward(float* db, float* dout, int r, int c) {
    for (int tid = 0; tid < c; ++tid) {
        float sum = 0.0f;
        for (int i = 0; i < r; ++i) {
            sum += dout[i * c + tid];
        }
        db[tid] += sum;
    }
}