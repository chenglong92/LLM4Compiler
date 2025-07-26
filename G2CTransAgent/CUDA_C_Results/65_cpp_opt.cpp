// Optimized code(id = 65): 

#include <cmath>

void variance_kernel(float* x, float* mean, int batch, int filters, int spatial, float* variance) {
    float scale = 1.f / (batch * spatial - 1);
    
    for (int i = 0; i < filters; ++i) {
        variance[i] = 0;
        
        for (int j = 0; j < batch; ++j) {
            for (int k = 0; k < spatial; ++k) {
                int index = j * filters * spatial + i * spatial + k;
                variance[i] += std::pow((x[index] - mean[i]), 2);
            }
        }
        
        variance[i] *= scale;
    }
}