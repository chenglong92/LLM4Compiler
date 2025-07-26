// original code(id = 107): 
 /*
__global__ void cudaSimpleCorrelator ( float * xi , float * xq , float * sr , float * si , int sLength , float * L , int uLength ) { int u = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( u >= uLength ) return ; float real = 0 ; float imag = 0 ; float a , b , c , d ; for ( int n = u ; n < u + sLength ; n ++ ) { a = xi [ n ] ; b = xq [ n ] ; c = sr [ n - u ] ; d = si [ n - u ] * ( -1 ) ; real += ( a * c ) - ( b * d ) ; imag += ( a * d ) + ( b * c ) ; } L [ u ] = sqrt ( real * real + imag * imag ) ; }
*/
// optimized code: 

#include <cmath>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

void cudaSimpleCorrelator(float* xi, float* xq, float* sr, float* si, int sLength, float* L, int uLength);

void testNormalCase() {
    const int sLength = 5;
    const int uLength = 3;
    
    float xi[sLength + uLength - 1] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f};
    float xq[sLength + uLength - 1] = {0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f};
    float sr[sLength] = {1.0f, 0.0f, -1.0f, 0.0f, 1.0f};
    float si[sLength] = {0.0f, 1.0f, 0.0f, -1.0f, 0.0f};
    float L[uLength] = {0};
    
    cudaSimpleCorrelator(xi, xq, sr, si, sLength, L, uLength);
    
    // Verify results
    float expected[uLength];
    for (int u = 0; u < uLength; ++u) {
        float real = 0;
        float imag = 0;
        for (int n = u; n < u + sLength; ++n) {
            float a = xi[n];
            float b = xq[n];
            float c = sr[n - u];
            float d = si[n - u] * (-1);
            real += (a * c) - (b * d);
            imag += (a * d) + (b * c);
        }
        expected[u] = sqrt(real * real + imag * imag);
        assert(fabs(L[u] - expected[u]) < 1e-6);
    }
    
    std::cout << "Normal case test passed." << std::endl;
}

void testBoundaryCase() {
    const int sLength = 1;
    const int uLength = 1;
    
    float xi[sLength + uLength - 1] = {1.0f};
    float xq[sLength + uLength - 1] = {0.5f};
    float sr[sLength] = {1.0f};
    float si[sLength] = {0.0f};
    float L[uLength] = {0};
    
    cudaSimpleCorrelator(xi, xq, sr, si, sLength, L, uLength);
    
    // Verify results
    float expected = sqrt(1.0f * 1.0f + 0.5f * 0.0f);
    assert(fabs(L[0] - expected) < 1e-6);
    
    std::cout << "Boundary case test passed." << std::endl;
}

void testRandomCase() {
    srand(time(0));
    const int sLength = 10;
    const int uLength = 5;
    
    float xi[sLength + uLength - 1];
    float xq[sLength + uLength - 1];
    float sr[sLength];
    float si[sLength];
    float L[uLength] = {0};
    
    // Generate random data
    for (int i = 0; i < sLength + uLength - 1; ++i) {
        xi[i] = static_cast<float>(rand()) / RAND_MAX;
        xq[i] = static_cast<float>(rand()) / RAND_MAX;
    }
    for (int i = 0; i < sLength; ++i) {
        sr[i] = static_cast<float>(rand()) / RAND_MAX;
        si[i] = static_cast<float>(rand()) / RAND_MAX;
    }
    
    cudaSimpleCorrelator(xi, xq, sr, si, sLength, L, uLength);
    
    // Verify results
    float expected[uLength];
    for (int u = 0; u < uLength; ++u) {
        float real = 0;
        float imag = 0;
        for (int n = u; n < u + sLength; ++n) {
            float a = xi[n];
            float b = xq[n];
            float c = sr[n - u];
            float d = si[n - u] * (-1);
            real += (a * c) - (b * d);
            imag += (a * d) + (b * c);
        }
        expected[u] = sqrt(real * real + imag * imag);
        assert(fabs(L[u] - expected[u]) < 1e-6);
    }
    
    std::cout << "Random case test passed." << std::endl;
}

void testZeroLengthCase() {
    const int sLength = 0;
    const int uLength = 0;
    
    float xi[1] = {0};
    float xq[1] = {0};
    float sr[1] = {0};
    float si[1] = {0};
    float L[1] = {0};
    
    // Should not crash
    cudaSimpleCorrelator(xi, xq, sr, si, sLength, L, uLength);
    
    std::cout << "Zero length case test passed." << std::endl;
}

int main() {
    testNormalCase();
    testBoundaryCase();
    testRandomCase();
    testZeroLengthCase();
    
    return 0;
}