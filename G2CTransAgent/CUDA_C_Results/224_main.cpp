// original code(id = 224): 
 /*
__global__ void cudaChoiLee ( float * xi , float * xq , float * sr , float * si , int N , float * L ) { int u = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( u >= N ) return ; float uSum = 0 ; float r_i , r_q , rconj_i , rconj_q ; float s_i , s_q , sconj_i , sconj_q ; float rsum_i , rsum_q , ssum_i , ssum_q ; float ksum_i , ksum_q ; for ( int i = 0 ; i < N ; i ++ ) { ksum_i = 0 ; ksum_q = 0 ; for ( int k = 0 ; k < N - i ; k ++ ) { r_i = xi [ u + k + i ] ; r_q = xq [ u + k + i ] ; rconj_i = xi [ u + k ] ; rconj_q = xq [ u + k ] * ( -1 ) ; s_i = sr [ k ] ; s_q = si [ k ] ; sconj_i = sr [ k + i ] ; sconj_q = si [ k + i ] * ( -1 ) ; rsum_i = ( r_i * rconj_i ) - ( r_q * rconj_q ) ; rsum_q = ( r_i * rconj_q ) + ( r_q * rconj_i ) ; ssum_i = ( s_i * sconj_i ) - ( s_q * sconj_q ) ; ssum_q = ( s_i * sconj_q ) + ( s_q * sconj_i ) ; ksum_i += ( rsum_i * ssum_i ) - ( rsum_q * ssum_q ) ; ksum_q += ( rsum_i * ssum_q ) + ( rsum_q * ssum_i ) ; } uSum += sqrt ( ( ksum_i * ksum_i ) + ( ksum_q * ksum_q ) ) ; } L [ u ] = uSum ; }
*/
// optimized code: 

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>

void cudaChoiLee(float* xi, float* xq, float* sr, float* si, int N, float* L) {
    for (int u = 0; u < N; ++u) {
        float uSum = 0;
        for (int i = 0; i < N; ++i) {
            float ksum_i = 0;
            float ksum_q = 0;
            for (int k = 0; k < N - i; ++k) {
                float r_i = xi[u + k + i];
                float r_q = xq[u + k + i];
                float rconj_i = xi[u + k];
                float rconj_q = xq[u + k] * (-1);
                
                float s_i = sr[k];
                float s_q = si[k];
                float sconj_i = sr[k + i];
                float sconj_q = si[k + i] * (-1);
                
                float rsum_i = (r_i * rconj_i) - (r_q * rconj_q);
                float rsum_q = (r_i * rconj_q) + (r_q * rconj_i);
                
                float ssum_i = (s_i * sconj_i) - (s_q * sconj_q);
                float ssum_q = (s_i * sconj_q) + (s_q * sconj_i);
                
                ksum_i += (rsum_i * ssum_i) - (rsum_q * ssum_q);
                ksum_q += (rsum_i * ssum_q) + (rsum_q * ssum_i);
            }
            uSum += sqrt((ksum_i * ksum_i) + (ksum_q * ksum_q));
        }
        L[u] = uSum;
    }
}

void printArray(float* arr, int size, const char* name) {
    std::cout << name << ": ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void testCase1() {
    const int N = 3;
    float xi[N] = {1.0f, 2.0f, 3.0f};
    float xq[N] = {0.5f, 1.5f, 2.5f};
    float sr[N] = {0.1f, 0.2f, 0.3f};
    float si[N] = {0.05f, 0.15f, 0.25f};
    float L[N] = {0};
    
    cudaChoiLee(xi, xq, sr, si, N, L);
    
    std::cout << "Test Case 1 (N=3):" << std::endl;
    printArray(xi, N, "xi");
    printArray(xq, N, "xq");
    printArray(sr, N, "sr");
    printArray(si, N, "si");
    printArray(L, N, "L");
    std::cout << std::endl;
}

void testCase2() {
    const int N = 1;
    float xi[N] = {1.0f};
    float xq[N] = {0.5f};
    float sr[N] = {0.1f};
    float si[N] = {0.05f};
    float L[N] = {0};
    
    cudaChoiLee(xi, xq, sr, si, N, L);
    
    std::cout << "Test Case 2 (N=1):" << std::endl;
    printArray(xi, N, "xi");
    printArray(xq, N, "xq");
    printArray(sr, N, "sr");
    printArray(si, N, "si");
    printArray(L, N, "L");
    std::cout << std::endl;
}

void testCase3() {
    const int N = 0;
    float* xi = nullptr;
    float* xq = nullptr;
    float* sr = nullptr;
    float* si = nullptr;
    float* L = nullptr;
    
    std::cout << "Test Case 3 (N=0):" << std::endl;
    cudaChoiLee(xi, xq, sr, si, N, L);
    std::cout << "Function called with N=0 (should handle gracefully)" << std::endl;
    std::cout << std::endl;
}

void testCase4() {
    const int N = 5;
    float xi[N], xq[N], sr[N], si[N], L[N];
    
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        xi[i] = static_cast<float>(rand()) / RAND_MAX;
        xq[i] = static_cast<float>(rand()) / RAND_MAX;
        sr[i] = static_cast<float>(rand()) / RAND_MAX;
        si[i] = static_cast<float>(rand()) / RAND_MAX;
    }
    
    cudaChoiLee(xi, xq, sr, si, N, L);
    
    std::cout << "Test Case 4 (N=5 with random values):" << std::endl;
    printArray(xi, N, "xi");
    printArray(xq, N, "xq");
    printArray(sr, N, "sr");
    printArray(si, N, "si");
    printArray(L, N, "L");
    std::cout << std::endl;
}

int main() {
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    
    return 0;
}