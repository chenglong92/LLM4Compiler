// original code(id = 29): 
 /*
__global__ void sgemm_kernelGPU ( const float * host_inputArray1 , const float * host_inputArray2 , float * host_inputArray3 , int M , int N , int K , float alpha , float beta ) { int column = blockIdx . x * blockDim . x + threadIdx . x ; int row = blockIdx . y * blockDim . y + threadIdx . y ; float element_c = 0.f ; for ( int eachElement = 0 ; eachElement < K ; eachElement ++ ) element_c += host_inputArray1 [ row * K + eachElement ] * host_inputArray2 [ eachElement * K + column ] ; host_inputArray3 [ row * N + column ] = alpha * element_c + beta * host_inputArray3 [ row * N + column ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void sgemm_kernelCPU(const float* host_inputArray1, const float* host_inputArray2, float* host_inputArray3, 
                     int M, int N, int K, float alpha, float beta);

void test_normal_case() {
    const int M = 2, N = 2, K = 2;
    float alpha = 1.0f, beta = 0.0f;
    
    float host_inputArray1[M*K] = {1.0f, 2.0f, 3.0f, 4.0f};
    float host_inputArray2[K*N] = {5.0f, 6.0f, 7.0f, 8.0f};
    float host_inputArray3[M*N] = {0};
    float expected[M*N] = {19.0f, 22.0f, 43.0f, 50.0f};
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    for (int i = 0; i < M*N; ++i) {
        assert(fabs(host_inputArray3[i] - expected[i]) < 1e-6);
    }
}

void test_edge_case_1x1() {
    const int M = 1, N = 1, K = 1;
    float alpha = 2.0f, beta = 3.0f;
    
    float host_inputArray1[M*K] = {2.0f};
    float host_inputArray2[K*N] = {3.0f};
    float host_inputArray3[M*N] = {4.0f};
    float expected = 2.0f * 2.0f * 3.0f + 3.0f * 4.0f;
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    assert(fabs(host_inputArray3[0] - expected) < 1e-6);
}

void test_alpha_beta_combinations() {
    const int M = 2, N = 2, K = 2;
    float alpha = 2.0f, beta = -1.0f;
    
    float host_inputArray1[M*K] = {1.0f, 0.0f, 0.0f, 1.0f};
    float host_inputArray2[K*N] = {1.0f, 0.0f, 0.0f, 1.0f};
    float host_inputArray3[M*N] = {1.0f, 1.0f, 1.0f, 1.0f};
    float expected[M*N] = {1.0f, -1.0f, -1.0f, 1.0f};
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    for (int i = 0; i < M*N; ++i) {
        assert(fabs(host_inputArray3[i] - expected[i]) < 1e-6);
    }
}

void test_non_square_matrices() {
    const int M = 2, N = 3, K = 4;
    float alpha = 1.0f, beta = 0.0f;
    
    float host_inputArray1[M*K] = {1,2,3,4,5,6,7,8};
    float host_inputArray2[K*N] = {1,0,0,0,1,0,0,0,1,0,0,0};
    float host_inputArray3[M*N] = {0};
    float expected[M*N] = {1,2,3,5,6,7};
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    for (int i = 0; i < M*N; ++i) {
        assert(fabs(host_inputArray3[i] - expected[i]) < 1e-6);
    }
}

void test_zero_matrix() {
    const int M = 3, N = 3, K = 3;
    float alpha = 1.0f, beta = 1.0f;
    
    float host_inputArray1[M*K] = {0};
    float host_inputArray2[K*N] = {0};
    float host_inputArray3[M*N] = {1,2,3,4,5,6,7,8,9};
    float expected[M*N] = {1,2,3,4,5,6,7,8,9};
    
    sgemm_kernelCPU(host_inputArray1, host_inputArray2, host_inputArray3, M, N, K, alpha, beta);
    
    for (int i = 0; i < M*N; ++i) {
        assert(fabs(host_inputArray3[i] - expected[i]) < 1e-6);
    }
}

int main() {
    test_normal_case();
    test_edge_case_1x1();
    test_alpha_beta_combinations();
    test_non_square_matrices();
    test_zero_matrix();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}