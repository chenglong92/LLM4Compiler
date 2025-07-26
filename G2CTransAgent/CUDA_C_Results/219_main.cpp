// original code(id = 219): 
 /*
__global__ void downsampleCuda ( float * I , float * Q , unsigned int numDownsampledSamples , float * downsampled_I , float * downsampled_Q , unsigned int factor ) { int sampleIndex = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( sampleIndex >= numDownsampledSamples ) return ; unsigned int absoluteIndex = sampleIndex * factor ; downsampled_I [ sampleIndex ] = I [ absoluteIndex ] ; downsampled_Q [ sampleIndex ] = Q [ absoluteIndex ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void downsampleCuda(float* I, float* Q, unsigned int numDownsampledSamples, float* downsampled_I, float* downsampled_Q, unsigned int factor);

int main() {
    // Test case 1: Basic downsampling with factor 2
    {
        const unsigned int numSamples = 10;
        const unsigned int factor = 2;
        const unsigned int numDownsampledSamples = numSamples / factor;
        
        float I[numSamples] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
        float Q[numSamples] = {10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        float downsampled_I[numDownsampledSamples];
        float downsampled_Q[numDownsampledSamples];
        
        downsampleCuda(I, Q, numDownsampledSamples, downsampled_I, downsampled_Q, factor);
        
        for (unsigned int i = 0; i < numDownsampledSamples; ++i) {
            assert(downsampled_I[i] == I[i * factor]);
            assert(downsampled_Q[i] == Q[i * factor]);
        }
    }
    
    // Test case 2: Downsampling with factor 1 (no change)
    {
        const unsigned int numSamples = 5;
        const unsigned int factor = 1;
        const unsigned int numDownsampledSamples = numSamples / factor;
        
        float I[numSamples] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        float Q[numSamples] = {5.5f, 4.4f, 3.3f, 2.2f, 1.1f};
        float downsampled_I[numDownsampledSamples];
        float downsampled_Q[numDownsampledSamples];
        
        downsampleCuda(I, Q, numDownsampledSamples, downsampled_I, downsampled_Q, factor);
        
        for (unsigned int i = 0; i < numDownsampledSamples; ++i) {
            assert(fabs(downsampled_I[i] - I[i * factor]) < 1e-6f);
            assert(fabs(downsampled_Q[i] - Q[i * factor]) < 1e-6f);
        }
    }
    
    // Test case 3: Downsampling with factor 3 (non-integer division)
    {
        const unsigned int numSamples = 10;
        const unsigned int factor = 3;
        const unsigned int numDownsampledSamples = numSamples / factor; // 3
        
        float I[numSamples] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};
        float Q[numSamples] = {10.0f, 9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        float downsampled_I[numDownsampledSamples];
        float downsampled_Q[numDownsampledSamples];
        
        downsampleCuda(I, Q, numDownsampledSamples, downsampled_I, downsampled_Q, factor);
        
        for (unsigned int i = 0; i < numDownsampledSamples; ++i) {
            assert(downsampled_I[i] == I[i * factor]);
            assert(downsampled_Q[i] == Q[i * factor]);
        }
    }
    
    // Test case 4: Empty input (numDownsampledSamples = 0)
    {
        const unsigned int numSamples = 0;
        const unsigned int factor = 2;
        const unsigned int numDownsampledSamples = numSamples / factor;
        
        float* I = nullptr;
        float* Q = nullptr;
        float downsampled_I[numDownsampledSamples];
        float downsampled_Q[numDownsampledSamples];
        
        downsampleCuda(I, Q, numDownsampledSamples, downsampled_I, downsampled_Q, factor);
        // No assertions needed as the function shouldn't do anything
    }
    
    // Test case 5: Large factor (greater than numSamples)
    {
        const unsigned int numSamples = 5;
        const unsigned int factor = 10;
        const unsigned int numDownsampledSamples = numSamples / factor; // 0
        
        float I[numSamples] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float Q[numSamples] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        float downsampled_I[numDownsampledSamples];
        float downsampled_Q[numDownsampledSamples];
        
        downsampleCuda(I, Q, numDownsampledSamples, downsampled_I, downsampled_Q, factor);
        // No assertions needed as the function shouldn't do anything
    }
    
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}