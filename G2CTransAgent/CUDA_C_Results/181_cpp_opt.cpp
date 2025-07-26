// Optimized code(id = 181): 

void MMDSelfComputeWithSum(float* x_average, int size_x, float* distance_matrix) {
    for (int i = 0; i < size_x; ++i) {
        for (int j = i; j < size_x; ++j) {
            distance_matrix[i * size_x + j] = x_average[i] * x_average[j];
        }
    }
}