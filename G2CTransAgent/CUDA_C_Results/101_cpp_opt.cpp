// Optimized code(id = 101): 

void l1_kernel(int n, float* pred, float* truth, float* delta, float* error) {
    for (int i = 0; i < n; ++i) {
        float diff = truth[i] - pred[i];
        error[i] = abs(diff);
        delta[i] = (diff > 0) ? 1.0f : -1.0f;
    }
}