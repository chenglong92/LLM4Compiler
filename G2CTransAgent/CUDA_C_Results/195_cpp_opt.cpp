// Optimized code(id = 195): 

void mean_kernel(float* x, int batch, int filters, int spatial, float* mean) {
    float scale = 1.f / (batch * spatial);
    for (int i = 0; i < filters; ++i) {
        mean[i] = 0;
        for (int j = 0; j < batch; ++j) {
            for (int k = 0; k < spatial; ++k) {
                int index = j * filters * spatial + i * spatial + k;
                mean[i] += x[index];
            }
        }
        mean[i] *= scale;
    }
}