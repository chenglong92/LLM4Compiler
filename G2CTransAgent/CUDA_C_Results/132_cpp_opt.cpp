// Optimized code(id = 132): 

#include <cmath>

void binarize_input_kernel(float* input, int n, int size, float* binary) {
    for (int s = 0; s < size; ++s) {
        float mean = 0;
        for (int i = 0; i < n; ++i) {
            mean += std::abs(input[i * size + s]);
        }
        mean = mean / n;
        
        for (int i = 0; i < n; ++i) {
            binary[i * size + s] = (input[i * size + s] > 0) ? mean : -mean;
        }
    }
}