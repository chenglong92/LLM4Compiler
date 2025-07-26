// original code(id = 103): 
 /*
__global__ void cudaAddCorrAndCorrection ( float * L , float * r , int N ) { int u = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( u >= N ) return ; L [ u ] -= r [ u ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

void cudaAddCorrAndCorrection(float* L, float* r, int N);

void testBasicSubtraction() {
    const int N = 5;
    float L[N] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
    float r[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float expected[N] = {9.0f, 18.0f, 27.0f, 36.0f, 45.0f};
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(L[i] == expected[i]);
    }
    std::cout << "testBasicSubtraction passed." << std::endl;
}

void testNegativeNumbers() {
    const int N = 4;
    float L[N] = {-5.0f, -10.0f, -15.0f, -20.0f};
    float r[N] = {2.0f, -3.0f, 5.0f, -7.0f};
    float expected[N] = {-7.0f, -7.0f, -20.0f, -13.0f};
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(L[i] == expected[i]);
    }
    std::cout << "testNegativeNumbers passed." << std::endl;
}

void testZeroValues() {
    const int N = 3;
    float L[N] = {0.0f, 0.0f, 0.0f};
    float r[N] = {0.0f, 1.0f, -1.0f};
    float expected[N] = {0.0f, -1.0f, 1.0f};
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(L[i] == expected[i]);
    }
    std::cout << "testZeroValues passed." << std::endl;
}

void testMixedNumbers() {
    const int N = 6;
    float L[N] = {100.0f, -50.0f, 0.0f, 25.5f, -10.25f, 3.14f};
    float r[N] = {50.0f, -25.0f, 10.0f, -12.5f, 5.125f, 1.59f};
    float expected[N] = {50.0f, -25.0f, -10.0f, 38.0f, -15.375f, 1.55f};
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(abs(L[i] - expected[i]) < 1e-6f);
    }
    std::cout << "testMixedNumbers passed." << std::endl;
}

void testEmptyArray() {
    const int N = 0;
    float* L = nullptr;
    float* r = nullptr;
    
    cudaAddCorrAndCorrection(L, r, N);
    std::cout << "testEmptyArray passed." << std::endl;
}

void testLargeArray() {
    const int N = 1000000;
    float* L = new float[N];
    float* r = new float[N];
    float* expected = new float[N];
    
    for (int i = 0; i < N; ++i) {
        L[i] = static_cast<float>(i);
        r[i] = static_cast<float>(i / 2);
        expected[i] = L[i] - r[i];
    }
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(L[i] == expected[i]);
    }
    
    delete[] L;
    delete[] r;
    delete[] expected;
    std::cout << "testLargeArray passed." << std::endl;
}

void testRandomValues() {
    std::srand(std::time(0));
    const int N = 1000;
    float L[N];
    float r[N];
    float expected[N];
    
    for (int i = 0; i < N; ++i) {
        L[i] = static_cast<float>(std::rand() % 10000 - 5000) / 100.0f;
        r[i] = static_cast<float>(std::rand() % 10000 - 5000) / 100.0f;
        expected[i] = L[i] - r[i];
    }
    
    cudaAddCorrAndCorrection(L, r, N);
    
    for (int i = 0; i < N; ++i) {
        assert(abs(L[i] - expected[i]) < 1e-6f);
    }
    std::cout << "testRandomValues passed." << std::endl;
}

int main() {
    testBasicSubtraction();
    testNegativeNumbers();
    testZeroValues();
    testMixedNumbers();
    testEmptyArray();
    testLargeArray();
    testRandomValues();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}