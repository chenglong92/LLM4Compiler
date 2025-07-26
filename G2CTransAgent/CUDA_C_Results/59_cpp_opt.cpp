// Optimized code(id = 59): 

void shortcut_kernel(int size, int minw, int minh, int minc, int stride, int sample, int batch, int w1, int h1, int c1, float* add, int w2, int h2, int c2, float* out) {
    for (int id = 0; id < size; ++id) {
        int i = id % minw;
        id /= minw;
        int j = id % minh;
        id /= minh;
        int k = id % minc;
        id /= minc;
        int b = id % batch;
        
        int out_index = i * sample + w2 * (j * sample + h2 * (k + c2 * b));
        int add_index = i * stride + w1 * (j * stride + h1 * (k + c1 * b));
        
        out[out_index] += add[add_index];
        
        // Restore id for the next iteration
        id = (b * minc + k) * minh + j;
        id = id * minw + i;
    }
}