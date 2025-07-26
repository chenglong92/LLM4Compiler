// original code(id = 176): 
 /*
__global__ void permuteDataTorch ( const float * input , float * output , int num , int devideNum , int featureSize , int priorNum , int batchSize ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= num ) { return ; } int numPerbatch = num * devideNum * priorNum ; for ( int s = 0 ; s < batchSize ; s ++ ) { for ( int i = 0 ; i < priorNum ; i ++ ) { for ( int j = 0 ; j < devideNum ; j ++ ) { output [ s * numPerbatch + tid * priorNum * devideNum + i * devideNum + j ] = input [ s * numPerbatch + ( i * devideNum * featureSize ) + ( j * featureSize ) + tid ] ; } } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstring>

void permuteDataTorch(const float* input, float* output, int num, int devideNum, int featureSize, int priorNum, int batchSize) {
    int numPerbatch = num * devideNum * priorNum;
    
    for (int tid = 0; tid < num; ++tid) {
        for (int s = 0; s < batchSize; ++s) {
            for (int i = 0; i < priorNum; ++i) {
                for (int j = 0; j < devideNum; ++j) {
                    output[s * numPerbatch + tid * priorNum * devideNum + i * devideNum + j] = 
                        input[s * numPerbatch + (i * devideNum * featureSize) + (j * featureSize) + tid];
                }
            }
        }
    }
}

void testNormalCase() {
    const int num = 2;
    const int devideNum = 3;
    const int featureSize = 4;
    const int priorNum = 2;
    const int batchSize = 2;
    
    const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
    const int outputSize = batchSize * num * devideNum * priorNum;
    
    float input[inputSize];
    float output[outputSize];
    
    for (int i = 0; i < inputSize; ++i) {
        input[i] = static_cast<float>(i);
    }
    
    permuteDataTorch(input, output, num, devideNum, featureSize, priorNum, batchSize);
    
    // Verify some sample positions
    assert(output[0] == input[0]);
    assert(output[1] == input[4]);
    assert(output[2] == input[8]);
    assert(output[3] == input[1]);
    assert(output[4] == input[5]);
    assert(output[5] == input[9]);
    assert(output[6] == input[48]);
    assert(output[7] == input[52]);
    assert(output[8] == input[56]);
    assert(output[9] == input[49]);
    assert(output[10] == input[53]);
    assert(output[11] == input[57]);
    
    std::cout << "Normal case test passed." << std::endl;
}

void testEdgeCaseSingleBatch() {
    const int num = 1;
    const int devideNum = 1;
    const int featureSize = 1;
    const int priorNum = 1;
    const int batchSize = 1;
    
    const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
    const int outputSize = batchSize * num * devideNum * priorNum;
    
    float input[inputSize] = {42.0f};
    float output[outputSize] = {0.0f};
    
    permuteDataTorch(input, output, num, devideNum, featureSize, priorNum, batchSize);
    
    assert(output[0] == input[0]);
    std::cout << "Edge case (single batch) test passed." << std::endl;
}

void testEdgeCaseLargeNumbers() {
    const int num = 100;
    const int devideNum = 100;
    const int featureSize = 100;
    const int priorNum = 100;
    const int batchSize = 10;
    
    const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
    const int outputSize = batchSize * num * devideNum * priorNum;
    
    float* input = new float[inputSize];
    float* output = new float[outputSize];
    
    for (int i = 0; i < inputSize; ++i) {
        input[i] = static_cast<float>(i);
    }
    
    permuteDataTorch(input, output, num, devideNum, featureSize, priorNum, batchSize);
    
    // Verify first and last elements
    assert(output[0] == input[0]);
    assert(output[outputSize-1] == input[inputSize-100]);
    
    delete[] input;
    delete[] output;
    std::cout << "Edge case (large numbers) test passed." << std::endl;
}

void testInvalidCaseZeroValues() {
    const int num = 0;
    const int devideNum = 0;
    const int featureSize = 0;
    const int priorNum = 0;
    const int batchSize = 0;
    
    const int inputSize = 1;  // Avoid zero-size array
    const int outputSize = 1; // Avoid zero-size array
    
    float input[inputSize] = {0.0f};
    float output[outputSize] = {0.0f};
    
    // Shouldn't crash with zero values
    permuteDataTorch(input, output, num, devideNum, featureSize, priorNum, batchSize);
    
    std::cout << "Invalid case (zero values) test passed (no crash)." << std::endl;
}

int main() {
    testNormalCase();
    testEdgeCaseSingleBatch();
    testEdgeCaseLargeNumbers();
    testInvalidCaseZeroValues();
    
    std::cout << "All tests completed successfully." << std::endl;
    return 0;
}