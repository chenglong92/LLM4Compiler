// Optimized code(id = 202): 

void logistic_x_ent(int n, float* pred, float* truth, float* delta, float* error) {
    for (int i = 0; i < n; ++i) {
        float t = truth[i];
        float p = pred[i];
        error[i] = -t * log(p + 0.0000001f) - (1 - t) * log(1 - p + 0.0000001f);
        delta[i] = t - p;
    }
}