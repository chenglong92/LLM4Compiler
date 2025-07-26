// Optimized code(id = 20): 

#include <iostream>

void runFilterCuda(float* I, float* Q, int samplesLength, float* filter, int filterLength, float* filtered_I, float* filtered_Q, int convLength) {
    for (int sampleIndex = 0; sampleIndex < convLength; ++sampleIndex) {
        float sumI = 0.0f;
        float sumQ = 0.0f;
        
        for (int j = sampleIndex - filterLength + 1; j <= sampleIndex; ++j) {
            int index = sampleIndex - j;
            if (j >= 0 && j < samplesLength) {
                sumI += filter[index] * I[j];
                sumQ += filter[index] * Q[j];
            }
        }
        
        filtered_I[sampleIndex] = sumI;
        filtered_Q[sampleIndex] = sumQ;
    }
}

// Example usage:
int main() {
    // Example parameters - adjust as needed
    const int samplesLength = 1000;
    const int filterLength = 100;
    const int convLength = samplesLength + filterLength - 1;
    
    float I[samplesLength];
    float Q[samplesLength];
    float filter[filterLength];
    float filtered_I[convLength];
    float filtered_Q[convLength];
    
    // Initialize arrays with some values
    for (int i = 0; i < samplesLength; ++i) {
        I[i] = static_cast<float>(i % 10);
        Q[i] = static_cast<float>((i + 5) % 10);
    }
    
    for (int i = 0; i < filterLength; ++i) {
        filter[i] = 1.0f / filterLength;  // Simple averaging filter
    }
    
    // Run the filter
    runFilterCuda(I, Q, samplesLength, filter, filterLength, filtered_I, filtered_Q, convLength);
    
    // Output some results for verification
    std::cout << "Filtered I[0]: " << filtered_I[0] << std::endl;
    std::cout << "Filtered Q[0]: " << filtered_Q[0] << std::endl;
    std::cout << "Filtered I[500]: " << filtered_I[500] << std::endl;
    std::cout << "Filtered Q[500]: " << filtered_Q[500] << std::endl;
    
    return 0;
}