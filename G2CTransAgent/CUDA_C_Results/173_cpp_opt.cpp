// Optimized code(id = 173): 

void kernel_CEE(float* x, int* t, float* loss, int r, int c) {
    int N = r;
    float temp;
    *loss = 0.0f; // Initialize loss
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < c; ++j) {
            if (t[i * c + j] == 1) {
                temp = logf(x[i * c + j] + 1e-7f);
                *loss += temp;
                break; // Assuming one-hot encoding (only one '1' per row)
            }
        }
    }
}