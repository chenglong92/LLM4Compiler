// original code(id = 19): 
 /*
__global__ void getTopkNum ( const float * inputScore , const int * inputIndex , float * outputScore , int * outputIndex , float threshold , const int dims , int * anchorIndex , int * classIndex , const int classNum , int batchSize , int totalScoreNum ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } for ( int i = 0 ; i < batchSize ; i ++ ) { if ( inputScore [ i * totalScoreNum + tid ] >= threshold ) { outputScore [ i * dims + tid ] = inputScore [ i * totalScoreNum + tid ] ; outputIndex [ i * dims + tid ] = inputIndex [ i * totalScoreNum + tid ] ; anchorIndex [ i * dims + tid ] = outputIndex [ i * dims + tid ] / classNum ; classIndex [ i * dims + tid ] = outputIndex [ i * dims + tid ] % classNum ; } else { outputScore [ i * dims + tid ] = 0.0f ; outputIndex [ i * dims + tid ] = -1 ; anchorIndex [ i * dims + tid ] = -1 ; classIndex [ i * dims + tid ] = -1 ; } } }
*/
// optimized code: 

#include <vector>
        #include <iostream>
        #include <cassert>

        void getTopkNum(const float* inputScore, const int* inputIndex, float* outputScore, int* outputIndex, 
                        float threshold, const int dims, int* anchorIndex, int* classIndex, 
                        const int classNum, int batchSize, int totalScoreNum);

        int main() {
            // Test case 1: Basic test with threshold condition met
            {
                const int batchSize = 2;
                const int dims = 3;
                const int classNum = 5;
                const int totalScoreNum = 10;
                float threshold = 0.5f;
                
                float inputScore[batchSize * totalScoreNum] = {
                    0.6f, 0.4f, 0.7f, 0.3f, 0.8f, 0.2f, 0.5f, 0.1f, 0.9f, 0.0f,
                    0.5f, 0.6f, 0.3f, 0.7f, 0.4f, 0.8f, 0.2f, 0.9f, 0.1f, 0.0f
                };
                
                int inputIndex[batchSize * totalScoreNum] = {
                    12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                    22, 23, 24, 25, 26, 27, 28, 29, 30, 31
                };
                
                float outputScore[batchSize * dims] = {0};
                int outputIndex[batchSize * dims] = {0};
                int anchorIndex[batchSize * dims] = {0};
                int classIndex[batchSize * dims] = {0};
                
                getTopkNum(inputScore, inputIndex, outputScore, outputIndex, threshold, dims, 
                          anchorIndex, classIndex, classNum, batchSize, totalScoreNum);
                
                // Verify results for batch 0
                assert(outputScore[0 * dims + 0] == 0.6f);
                assert(outputIndex[0 * dims + 0] == 12);
                assert(anchorIndex[0 * dims + 0] == 12 / classNum);
                assert(classIndex[0 * dims + 0] == 12 % classNum);
                
                assert(outputScore[0 * dims + 1] == 0.0f); // Below threshold
                assert(outputIndex[0 * dims + 1] == -1);
                assert(anchorIndex[0 * dims + 1] == -1);
                assert(classIndex[0 * dims + 1] == -1);
                
                assert(outputScore[0 * dims + 2] == 0.7f);
                assert(outputIndex[0 * dims + 2] == 14);
                assert(anchorIndex[0 * dims + 2] == 14 / classNum);
                assert(classIndex[0 * dims + 2] == 14 % classNum);
                
                // Verify results for batch 1
                assert(outputScore[1 * dims + 0] == 0.5f);
                assert(outputIndex[1 * dims + 0] == 22);
                assert(anchorIndex[1 * dims + 0] == 22 / classNum);
                assert(classIndex[1 * dims + 0] == 22 % classNum);
                
                assert(outputScore[1 * dims + 1] == 0.6f);
                assert(outputIndex[1 * dims + 1] == 23);
                assert(anchorIndex[1 * dims + 1] == 23 / classNum);
                assert(classIndex[1 * dims + 1] == 23 % classNum);
                
                assert(outputScore[1 * dims + 2] == 0.0f); // Below threshold
                assert(outputIndex[1 * dims + 2] == -1);
                assert(anchorIndex[1 * dims + 2] == -1);
                assert(classIndex[1 * dims + 2] == -1);
            }
            
            // Test case 2: All scores below threshold
            {
                const int batchSize = 1;
                const int dims = 2;
                const int classNum = 3;
                const int totalScoreNum = 5;
                float threshold = 0.9f;
                
                float inputScore[batchSize * totalScoreNum] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
                int inputIndex[batchSize * totalScoreNum] = {10, 11, 12, 13, 14};
                
                float outputScore[batchSize * dims] = {-1.0f};
                int outputIndex[batchSize * dims] = {-2};
                int anchorIndex[batchSize * dims] = {-3};
                int classIndex[batchSize * dims] = {-4};
                
                getTopkNum(inputScore, inputIndex, outputScore, outputIndex, threshold, dims, 
                          anchorIndex, classIndex, classNum, batchSize, totalScoreNum);
                
                for (int i = 0; i < batchSize * dims; ++i) {
                    assert(outputScore[i] == 0.0f);
                    assert(outputIndex[i] == -1);
                    assert(anchorIndex[i] == -1);
                    assert(classIndex[i] == -1);
                }
            }
            
            // Test case 3: Edge case with single element and threshold exactly matched
            {
                const int batchSize = 1;
                const int dims = 1;
                const int classNum = 2;
                const int totalScoreNum = 1;
                float threshold = 0.5f;
                
                float inputScore[batchSize * totalScoreNum] = {0.5f};
                int inputIndex[batchSize * totalScoreNum] = {3};
                
                float outputScore[batchSize * dims] = {0.0f};
                int outputIndex[batchSize * dims] = {0};
                int anchorIndex[batchSize * dims] = {0};
                int classIndex[batchSize * dims] = {0};
                
                getTopkNum(inputScore, inputIndex, outputScore, outputIndex, threshold, dims, 
                          anchorIndex, classIndex, classNum, batchSize, totalScoreNum);
                
                assert(outputScore[0] == 0.5f);
                assert(outputIndex[0] == 3);
                assert(anchorIndex[0] == 3 / classNum);
                assert(classIndex[0] == 3 % classNum);
            }
            
            // Test case 4: Multiple batches with varying conditions
            {
                const int batchSize = 3;
                const int dims = 4;
                const int classNum = 10;
                const int totalScoreNum = 8;
                float threshold = 0.6f;
                
                float inputScore[batchSize * totalScoreNum] = {
                    0.7f, 0.5f, 0.6f, 0.4f, 0.8f, 0.3f, 0.9f, 0.2f,
                    0.1f, 0.6f, 0.7f, 0.5f, 0.4f, 0.8f, 0.2f, 0.9f,
                    0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f
                };
                
                int inputIndex[batchSize * totalScoreNum] = {
                    15, 16, 17, 18, 19, 20, 21, 22,
                    23, 24, 25, 26, 27, 28, 29, 30,
                    31, 32, 33, 34, 35, 36, 37, 38
                };
                
                float outputScore[batchSize * dims] = {0};
                int outputIndex[batchSize * dims] = {0};
                int anchorIndex[batchSize * dims] = {0};
                int classIndex[batchSize * dims] = {0};
                
                getTopkNum(inputScore, inputIndex, outputScore, outputIndex, threshold, dims, 
                          anchorIndex, classIndex, classNum, batchSize, totalScoreNum);
                
                // Verify batch 0
                assert(outputScore[0 * dims + 0] == 0.7f);
                assert(outputIndex[0 * dims + 0] == 15);
                assert(anchorIndex[0 * dims + 0] == 15 / classNum);
                assert(classIndex[0 * dims + 0] == 15 % classNum);
                
                assert(outputScore[0 * dims + 1] == 0.0f); // Below threshold
                assert(outputIndex[0 * dims + 1] == -1);
                assert(anchorIndex[0 * dims + 1] == -1);
                assert(classIndex[0 * dims + 1] == -1);
                
                assert(outputScore[0 * dims + 2] == 0.6f);
                assert(outputIndex[0 * dims + 2] == 17);
                assert(anchorIndex[0 * dims + 2] == 17 / classNum);
                assert(classIndex[0 * dims + 2] == 17 % classNum);
                
                assert(outputScore[0 * dims + 3] == 0.0f); // Below threshold
                assert(outputIndex[0 * dims + 3] == -1);
                assert(anchorIndex[0 * dims + 3] == -1);
                assert(classIndex[0 * dims + 3] == -1);
                
                // Verify batch 1
                assert(outputScore[1 * dims + 0] == 0.0f); // Below threshold
                assert(outputIndex[1 * dims + 0] == -1);
                assert(anchorIndex[1 * dims + 0] == -1);
                assert(classIndex[1 * dims + 0] == -1);
                
                assert(outputScore[1 * dims + 1] == 0.6f);
                assert(outputIndex[1 * dims + 1] == 24);
                assert(anchorIndex[1 * dims + 1] == 24 / classNum);
                assert(classIndex[1 * dims + 1] == 24 % classNum);
                
                assert(outputScore[1 * dims + 2] == 0.7f);
                assert(outputIndex[1 * dims + 2] == 25);
                assert(anchorIndex[1 * dims + 2] == 25 / classNum);
                assert(classIndex[1 * dims + 2] == 25 % classNum);
                
                assert(outputScore[1 * dims + 3] == 0.0f); // Below threshold
                assert(outputIndex[1 * dims + 3] == -1);
                assert(anchorIndex[1 * dims + 3] == -1);
                assert(classIndex[1 * dims + 3] == -1);
                
                // Verify batch 2 (all exactly at threshold)
                for (int i = 0; i < dims; ++i) {
                    assert(outputScore[2 * dims + i] == 0.6f);
                    assert(outputIndex[2 * dims + i] == 31 + i);
                    assert(anchorIndex[2 * dims + i] == (31 + i) / classNum);
                    assert(classIndex[2 * dims + i] == (31 + i) % classNum);
                }
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }