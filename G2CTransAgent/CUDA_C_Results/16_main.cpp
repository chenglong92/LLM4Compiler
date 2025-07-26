// original code(id = 16): 
 /*
__global__ void cudaKernel_estimateSnr ( const float * corrSum , const int * corrValidCount , const float * maxval , float * snrValue , const int size ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx >= size ) return ; float mean = ( corrSum [ idx ] - maxval [ idx ] * maxval [ idx ] ) / ( corrValidCount [ idx ] - 1 ) ; snrValue [ idx ] = maxval [ idx ] * maxval [ idx ] / mean ; }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void estimateSnr(const float* corrSum, const int* corrValidCount, const float* maxval, float* snrValue, const int size) {
    for (int idx = 0; idx < size; ++idx) {
        float mean = (corrSum[idx] - maxval[idx] * maxval[idx]) / (corrValidCount[idx] - 1);
        snrValue[idx] = maxval[idx] * maxval[idx] / mean;
    }
}

void testEstimateSnr() {
    // Test case 1: Basic test with positive values
    {
        const int size = 3;
        float corrSum[] = {10.0f, 20.0f, 30.0f};
        int corrValidCount[] = {5, 6, 7};
        float maxval[] = {2.0f, 3.0f, 4.0f};
        float snrValue[size];
        
        estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);
        
        assert(fabs(snrValue[0] - (4.0f / ((10.0f - 4.0f) / 4))) < 1e-6);
        assert(fabs(snrValue[1] - (9.0f / ((20.0f - 9.0f) / 5))) < 1e-6);
        assert(fabs(snrValue[2] - (16.0f / ((30.0f - 16.0f) / 6))) < 1e-6);
    }
    
    // Test case 2: Edge case with corrValidCount = 1 (should be handled carefully in real implementation)
    {
        const int size = 2;
        float corrSum[] = {5.0f, 10.0f};
        int corrValidCount[] = {1, 2};
        float maxval[] = {2.0f, 3.0f};
        float snrValue[size];
        
        estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);
        // Note: Division by zero is undefined behavior, this test case is for demonstration only
    }
    
    // Test case 3: All zero values
    {
        const int size = 2;
        float corrSum[] = {0.0f, 0.0f};
        int corrValidCount[] = {2, 3};
        float maxval[] = {0.0f, 0.0f};
        float snrValue[size];
        
        estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);
        
        assert(std::isnan(snrValue[0]));
        assert(std::isnan(snrValue[1]));
    }
    
    // Test case 4: Negative maxval values
    {
        const int size = 2;
        float corrSum[] = {10.0f, 20.0f};
        int corrValidCount[] = {5, 6};
        float maxval[] = {-2.0f, -3.0f};
        float snrValue[size];
        
        estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);
        
        assert(fabs(snrValue[0] - (4.0f / ((10.0f - 4.0f) / 4))) < 1e-6);
        assert(fabs(snrValue[1] - (9.0f / ((20.0f - 9.0f) / 5))) < 1e-6);
    }
    
    // Test case 5: Single element array
    {
        const int size = 1;
        float corrSum[] = {15.0f};
        int corrValidCount[] = {4};
        float maxval[] = {3.0f};
        float snrValue[size];
        
        estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);
        
        assert(fabs(snrValue[0] - (9.0f / ((15.0f - 9.0f) / 3))) < 1e-6);
    }
}

int main() {
    testEstimateSnr();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}