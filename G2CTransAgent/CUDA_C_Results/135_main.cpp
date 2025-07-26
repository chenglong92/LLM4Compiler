// original code(id = 135): 
 /*
__global__ void cudaRunComplexFilter ( float * I , float * Q , int samplesLength , float * hr , float * hi , int filterLength , float * filtered_I , float * filtered_Q , int convLength ) { int sampleIndex = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( sampleIndex >= convLength ) return ; int index ; float sumI , sumQ ; sumI = 0 ; sumQ = 0 ; for ( int j = sampleIndex - filterLength + 1 ; j <= sampleIndex ; j ++ ) { index = sampleIndex - j ; if ( ( j < samplesLength ) && ( j >= 0 ) ) { sumI += ( I [ j ] * hr [ index ] ) - ( Q [ j ] * hi [ index ] ) ; sumQ += ( I [ j ] * hi [ index ] ) + ( Q [ j ] * hr [ index ] ) ; } } filtered_I [ sampleIndex ] = sumI ; filtered_Q [ sampleIndex ] = sumQ ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void cudaRunComplexFilter(float* I, float* Q, int samplesLength, float* hr, float* hi, int filterLength, float* filtered_I, float* filtered_Q, int convLength) {
    for (int sampleIndex = 0; sampleIndex < convLength; ++sampleIndex) {
        float sumI = 0;
        float sumQ = 0;
        
        for (int j = sampleIndex - filterLength + 1; j <= sampleIndex; ++j) {
            int index = sampleIndex - j;
            if ((j < samplesLength) && (j >= 0)) {
                sumI += (I[j] * hr[index]) - (Q[j] * hi[index]);
                sumQ += (I[j] * hi[index]) + (Q[j] * hr[index]);
            }
        }
        
        filtered_I[sampleIndex] = sumI;
        filtered_Q[sampleIndex] = sumQ;
    }
}

int main() {
    // Test case 1: Basic test with small arrays
    {
        float I[] = {1.0f, 2.0f, 3.0f};
        float Q[] = {0.5f, 1.5f, 2.5f};
        int samplesLength = 3;
        float hr[] = {0.5f, 0.25f};
        float hi[] = {0.1f, 0.2f};
        int filterLength = 2;
        int convLength = 4;
        float filtered_I[4] = {0};
        float filtered_Q[4] = {0};
        
        cudaRunComplexFilter(I, Q, samplesLength, hr, hi, filterLength, filtered_I, filtered_Q, convLength);
        
        assert(fabs(filtered_I[0] - (I[0]*hr[0] - Q[0]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[0] - (I[0]*hi[0] + Q[0]*hr[0])) < 1e-6);
        assert(fabs(filtered_I[1] - (I[0]*hr[1] - Q[0]*hi[1] + I[1]*hr[0] - Q[1]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[1] - (I[0]*hi[1] + Q[0]*hr[1] + I[1]*hi[0] + Q[1]*hr[0])) < 1e-6);
    }
    
    // Test case 2: Edge case with empty input
    {
        float I[] = {};
        float Q[] = {};
        int samplesLength = 0;
        float hr[] = {0.5f};
        float hi[] = {0.1f};
        int filterLength = 1;
        int convLength = 1;
        float filtered_I[1] = {0};
        float filtered_Q[1] = {0};
        
        cudaRunComplexFilter(I, Q, samplesLength, hr, hi, filterLength, filtered_I, filtered_Q, convLength);
        
        assert(filtered_I[0] == 0.0f);
        assert(filtered_Q[0] == 0.0f);
    }
    
    // Test case 3: Filter longer than input
    {
        float I[] = {1.0f, 2.0f};
        float Q[] = {0.5f, 1.0f};
        int samplesLength = 2;
        float hr[] = {0.5f, 0.25f, 0.125f};
        float hi[] = {0.1f, 0.2f, 0.3f};
        int filterLength = 3;
        int convLength = 4;
        float filtered_I[4] = {0};
        float filtered_Q[4] = {0};
        
        cudaRunComplexFilter(I, Q, samplesLength, hr, hi, filterLength, filtered_I, filtered_Q, convLength);
        
        assert(fabs(filtered_I[0] - (I[0]*hr[0] - Q[0]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[0] - (I[0]*hi[0] + Q[0]*hr[0])) < 1e-6);
        assert(fabs(filtered_I[1] - (I[0]*hr[1] - Q[0]*hi[1] + I[1]*hr[0] - Q[1]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[1] - (I[0]*hi[1] + Q[0]*hr[1] + I[1]*hi[0] + Q[1]*hr[0])) < 1e-6);
        assert(fabs(filtered_I[2] - (I[0]*hr[2] - Q[0]*hi[2] + I[1]*hr[1] - Q[1]*hi[1])) < 1e-6);
        assert(fabs(filtered_Q[2] - (I[0]*hi[2] + Q[0]*hr[2] + I[1]*hi[1] + Q[1]*hr[1])) < 1e-6);
    }
    
    // Test case 4: convLength smaller than filterLength
    {
        float I[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float Q[] = {0.1f, 0.2f, 0.3f, 0.4f};
        int samplesLength = 4;
        float hr[] = {0.5f, 0.25f, 0.125f};
        float hi[] = {0.1f, 0.2f, 0.3f};
        int filterLength = 3;
        int convLength = 2;
        float filtered_I[2] = {0};
        float filtered_Q[2] = {0};
        
        cudaRunComplexFilter(I, Q, samplesLength, hr, hi, filterLength, filtered_I, filtered_Q, convLength);
        
        assert(fabs(filtered_I[0] - (I[0]*hr[0] - Q[0]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[0] - (I[0]*hi[0] + Q[0]*hr[0])) < 1e-6);
        assert(fabs(filtered_I[1] - (I[0]*hr[1] - Q[0]*hi[1] + I[1]*hr[0] - Q[1]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[1] - (I[0]*hi[1] + Q[0]*hr[1] + I[1]*hi[0] + Q[1]*hr[0])) < 1e-6);
    }
    
    // Test case 5: Negative values in input
    {
        float I[] = {-1.0f, 2.0f, -3.0f};
        float Q[] = {0.5f, -1.5f, 2.5f};
        int samplesLength = 3;
        float hr[] = {0.5f, -0.25f};
        float hi[] = {0.1f, -0.2f};
        int filterLength = 2;
        int convLength = 4;
        float filtered_I[4] = {0};
        float filtered_Q[4] = {0};
        
        cudaRunComplexFilter(I, Q, samplesLength, hr, hi, filterLength, filtered_I, filtered_Q, convLength);
        
        assert(fabs(filtered_I[0] - (I[0]*hr[0] - Q[0]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[0] - (I[0]*hi[0] + Q[0]*hr[0])) < 1e-6);
        assert(fabs(filtered_I[1] - (I[0]*hr[1] - Q[0]*hi[1] + I[1]*hr[0] - Q[1]*hi[0])) < 1e-6);
        assert(fabs(filtered_Q[1] - (I[0]*hi[1] + Q[0]*hr[1] + I[1]*hi[0] + Q[1]*hr[0])) < 1e-6);
    }
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}