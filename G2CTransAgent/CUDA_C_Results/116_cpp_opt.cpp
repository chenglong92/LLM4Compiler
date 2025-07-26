// Optimized code(id = 116): 

void Kernel_Avg(float* dev_arrayMax, float* dev_array, const int r, const int c) {
    for (int i = 0; i < r; ++i) {
        float sum = 0.0f;
        for (int j = 0; j < c; ++j) {
            sum += dev_array[i * c + j];
        }
        dev_arrayMax[i] = sum / c;
    }
}