// Optimized code(id = 215): 

void l2_kernel(int n, float* pred, float* truth, float* delta, float* error) {
            for (int i = 0; i < n; ++i) {
                float diff = truth[i] - pred[i];
                error[i] = diff * diff;
                delta[i] = diff;
            }
        }