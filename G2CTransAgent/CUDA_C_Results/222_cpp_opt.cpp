// Optimized code(id = 222): 

#include <cmath>

        void cuda_Adam_step_kernel(float* grad, float* data, float* m, float* v, bool decay, float weight_decay, float beta1, float beta2, float eps, float step_size, int varsize) {
            for (int i = 0; i < varsize; ++i) {
                float g = grad[i];
                if (decay) {
                    g += weight_decay * data[i];
                }
                m[i] = beta1 * m[i] + (1.0f - beta1) * g;
                v[i] = beta2 * v[i] + (1.0f - beta2) * g * g;
                data[i] -= step_size * m[i] / (sqrtf(v[i]) + eps);
            }
        }