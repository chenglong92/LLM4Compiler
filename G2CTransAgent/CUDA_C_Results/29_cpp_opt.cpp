// Optimized code(id = 29): 

#include <iostream>

void sgemm_kernelCPU(const float* host_inputArray1, const float* host_inputArray2, float* host_inputArray3, 
                     int M, int N, int K, float alpha, float beta) {
    for (int row = 0; row < M; ++row) {
        for (int column = 0; column < N; ++column) {
            float element_c = 0.f;
            for (int eachElement = 0; eachElement < K; ++eachElement) {
                element_c += host_inputArray1[row * K + eachElement] * 
                            host_inputArray2[eachElement * N + column];  // Fixed index calculation
            }
            host_inputArray3[row * N + column] = alpha * element_c + 
                                               beta * host_inputArray3[row * N + column];
        }
    }
}

// Example usage:
int main() {
    const int M = 4, N = 4, K = 4;
    float alpha = 1.0f, beta = 1.0f;
    
    float* host_inputArray1 = new float[M*K];
    float* host_inputArray2 = new float[K*N];
    float* host_inputArray3 = new float[M*N];
    
    // Initialize arrays with some values
    for (int i = 0; i < M*K; ++i) host_inputArray1[i] = 1.0f;
    for (int i = 0; i < K*N; ++i) host_inputArray2[i] = 1.0f;
    for (int i = 0; i < M*N; ++i) host_inputArray3[i] = 0.0f;
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    // Print results
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << host_inputArray3[i*N + j] << " ";
        }
        std::cout << std::endl;
    }
    
    delete[] host_inputArray1;
    delete[] host_inputArray2;
    delete[] host_inputArray3;
    
    return 0;
}