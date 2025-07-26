// original code(id = 88): 
 /*
__global__ void permuteData ( const float * input , float * output , int num , int devideNum , int featureSize , int priorNum , int batchSize ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= num ) { return ; } int numPerbatch = num * devideNum * priorNum ; for ( int s = 0 ; s < batchSize ; s ++ ) { for ( int i = 0 ; i < priorNum ; i ++ ) { for ( int j = 0 ; j < devideNum ; j ++ ) { output [ s * numPerbatch + tid * priorNum * devideNum + i * devideNum + j ] = input [ s * numPerbatch + ( i * devideNum * featureSize ) + ( j * featureSize ) + tid ] ; } } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void permuteData(const float* input, float* output, int num, int devideNum, int featureSize, int priorNum, int batchSize) {
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
            
            // Initialize input with sequential values
            for (int i = 0; i < inputSize; ++i) {
                input[i] = static_cast<float>(i);
            }
            
            permuteData(input, output, num, devideNum, featureSize, priorNum, batchSize);
            
            // Verify some expected values
            assert(output[0] == input[0]);
            assert(output[1] == input[4]);
            assert(output[2] == input[8]);
            assert(output[3] == input[1]);
            assert(output[4] == input[5]);
            assert(output[5] == input[9]);
            assert(output[6] == input[24]);
            assert(output[7] == input[28]);
            assert(output[8] == input[32]);
            assert(output[9] == input[25]);
            assert(output[10] == input[29]);
            assert(output[11] == input[33]);
            
            std::cout << "Normal case test passed!" << std::endl;
        }

        void testMinimalCase() {
            const int num = 1;
            const int devideNum = 1;
            const int featureSize = 1;
            const int priorNum = 1;
            const int batchSize = 1;
            
            const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
            const int outputSize = batchSize * num * devideNum * priorNum;
            
            float input[inputSize] = {5.0f};
            float output[outputSize] = {0.0f};
            
            permuteData(input, output, num, devideNum, featureSize, priorNum, batchSize);
            
            assert(output[0] == input[0]);
            
            std::cout << "Minimal case test passed!" << std::endl;
        }

        void testDifferentDimensions() {
            const int num = 3;
            const int devideNum = 2;
            const int featureSize = 5;
            const int priorNum = 4;
            const int batchSize = 3;
            
            const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
            const int outputSize = batchSize * num * devideNum * priorNum;
            
            float input[inputSize];
            float output[outputSize];
            
            // Initialize input with sequential values
            for (int i = 0; i < inputSize; ++i) {
                input[i] = static_cast<float>(i);
            }
            
            permuteData(input, output, num, devideNum, featureSize, priorNum, batchSize);
            
            // Verify some expected values
            assert(output[0] == input[0]);
            assert(output[1] == input[10]);
            assert(output[2] == input[5]);
            assert(output[3] == input[15]);
            assert(output[4] == input[1]);
            assert(output[5] == input[11]);
            assert(output[6] == input[6]);
            assert(output[7] == input[16]);
            assert(output[120] == input[600]);
            assert(output[121] == input[610]);
            assert(output[122] == input[605]);
            assert(output[123] == input[615]);
            
            std::cout << "Different dimensions test passed!" << std::endl;
        }

        void testLargeBatch() {
            const int num = 2;
            const int devideNum = 2;
            const int featureSize = 3;
            const int priorNum = 2;
            const int batchSize = 100;
            
            const int inputSize = batchSize * num * devideNum * priorNum * featureSize;
            const int outputSize = batchSize * num * devideNum * priorNum;
            
            float* input = new float[inputSize];
            float* output = new float[outputSize];
            
            // Initialize input with sequential values
            for (int i = 0; i < inputSize; ++i) {
                input[i] = static_cast<float>(i);
            }
            
            permuteData(input, output, num, devideNum, featureSize, priorNum, batchSize);
            
            // Verify some expected values
            assert(output[0] == input[0]);
            assert(output[1] == input[6]);
            assert(output[2] == input[3]);
            assert(output[3] == input[9]);
            assert(output[4] == input[1]);
            assert(output[5] == input[7]);
            assert(output[6] == input[4]);
            assert(output[7] == input[10]);
            assert(output[796] == input[2388]);
            assert(output[797] == input[2394]);
            assert(output[798] == input[2391]);
            assert(output[799] == input[2397]);
            
            delete[] input;
            delete[] output;
            
            std::cout << "Large batch test passed!" << std::endl;
        }

        int main() {
            testNormalCase();
            testMinimalCase();
            testDifferentDimensions();
            testLargeBatch();
            
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }