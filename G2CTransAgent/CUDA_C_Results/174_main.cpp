// original code(id = 174): 
 /*
__global__ void permuteData2 ( const float * input , float * output , int num , int devideNum , int featureSize , int priorNum , int batchSize ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= num ) { return ; } int numPerbatch = num * devideNum * priorNum ; for ( int s = 0 ; s < batchSize ; s ++ ) { for ( int i = 0 ; i < priorNum ; i ++ ) { for ( int j = 0 ; j < devideNum ; j ++ ) { output [ s * numPerbatch + tid * priorNum * devideNum + i * devideNum + j ] = input [ s * numPerbatch + ( i * devideNum * featureSize ) + ( j * featureSize ) + tid ] ; } } } }
*/
// optimized code: 

#include <vector>
#include <iostream>
#include <cassert>

void permuteData2(const float* input, float* output, int num, int devideNum, int featureSize, int priorNum, int batchSize);

int main() {
    // Test case 1: Small input with batchSize=1, num=2, devideNum=3, featureSize=4, priorNum=5
    {
        int num = 2;
        int devideNum = 3;
        int featureSize = 4;
        int priorNum = 5;
        int batchSize = 1;
        
        int inputSize = batchSize * num * devideNum * priorNum * featureSize;
        std::vector<float> input(inputSize);
        for (int i = 0; i < inputSize; ++i) {
            input[i] = static_cast<float>(i);
        }
        
        int outputSize = batchSize * num * devideNum * priorNum;
        std::vector<float> output(outputSize, 0.0f);
        
        permuteData2(input.data(), output.data(), num, devideNum, featureSize, priorNum, batchSize);
        
        // Verify the output
        for (int s = 0; s < batchSize; ++s) {
            for (int tid = 0; tid < num; ++tid) {
                for (int i = 0; i < priorNum; ++i) {
                    for (int j = 0; j < devideNum; ++j) {
                        int outputIdx = s * num * devideNum * priorNum + tid * priorNum * devideNum + i * devideNum + j;
                        int inputIdx = s * num * devideNum * priorNum * featureSize + (i * devideNum * featureSize) + (j * featureSize) + tid;
                        assert(output[outputIdx] == input[inputIdx]);
                    }
                }
            }
        }
    }
    
    // Test case 2: Larger batch size (batchSize=2)
    {
        int num = 2;
        int devideNum = 3;
        int featureSize = 4;
        int priorNum = 5;
        int batchSize = 2;
        
        int inputSize = batchSize * num * devideNum * priorNum * featureSize;
        std::vector<float> input(inputSize);
        for (int i = 0; i < inputSize; ++i) {
            input[i] = static_cast<float>(i);
        }
        
        int outputSize = batchSize * num * devideNum * priorNum;
        std::vector<float> output(outputSize, 0.0f);
        
        permuteData2(input.data(), output.data(), num, devideNum, featureSize, priorNum, batchSize);
        
        // Verify the output
        for (int s = 0; s < batchSize; ++s) {
            for (int tid = 0; tid < num; ++tid) {
                for (int i = 0; i < priorNum; ++i) {
                    for (int j = 0; j < devideNum; ++j) {
                        int outputIdx = s * num * devideNum * priorNum + tid * priorNum * devideNum + i * devideNum + j;
                        int inputIdx = s * num * devideNum * priorNum * featureSize + (i * devideNum * featureSize) + (j * featureSize) + tid;
                        assert(output[outputIdx] == input[inputIdx]);
                    }
                }
            }
        }
    }
    
    // Test case 3: Minimum values for all parameters
    {
        int num = 1;
        int devideNum = 1;
        int featureSize = 1;
        int priorNum = 1;
        int batchSize = 1;
        
        int inputSize = batchSize * num * devideNum * priorNum * featureSize;
        std::vector<float> input(inputSize);
        for (int i = 0; i < inputSize; ++i) {
            input[i] = static_cast<float>(i);
        }
        
        int outputSize = batchSize * num * devideNum * priorNum;
        std::vector<float> output(outputSize, 0.0f);
        
        permuteData2(input.data(), output.data(), num, devideNum, featureSize, priorNum, batchSize);
        
        // Verify the output
        for (int s = 0; s < batchSize; ++s) {
            for (int tid = 0; tid < num; ++tid) {
                for (int i = 0; i < priorNum; ++i) {
                    for (int j = 0; j < devideNum; ++j) {
                        int outputIdx = s * num * devideNum * priorNum + tid * priorNum * devideNum + i * devideNum + j;
                        int inputIdx = s * num * devideNum * priorNum * featureSize + (i * devideNum * featureSize) + (j * featureSize) + tid;
                        assert(output[outputIdx] == input[inputIdx]);
                    }
                }
            }
        }
    }
    
    // Test case 4: Different featureSize (featureSize=2)
    {
        int num = 2;
        int devideNum = 3;
        int featureSize = 2;
        int priorNum = 4;
        int batchSize = 1;
        
        int inputSize = batchSize * num * devideNum * priorNum * featureSize;
        std::vector<float> input(inputSize);
        for (int i = 0; i < inputSize; ++i) {
            input[i] = static_cast<float>(i);
        }
        
        int outputSize = batchSize * num * devideNum * priorNum;
        std::vector<float> output(outputSize, 0.0f);
        
        permuteData2(input.data(), output.data(), num, devideNum, featureSize, priorNum, batchSize);
        
        // Verify the output
        for (int s = 0; s < batchSize; ++s) {
            for (int tid = 0; tid < num; ++tid) {
                for (int i = 0; i < priorNum; ++i) {
                    for (int j = 0; j < devideNum; ++j) {
                        int outputIdx = s * num * devideNum * priorNum + tid * priorNum * devideNum + i * devideNum + j;
                        int inputIdx = s * num * devideNum * priorNum * featureSize + (i * devideNum * featureSize) + (j * featureSize) + tid;
                        assert(output[outputIdx] == input[inputIdx]);
                    }
                }
            }
        }
    }
    
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}