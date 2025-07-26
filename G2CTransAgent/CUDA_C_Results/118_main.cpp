// original code(id = 118): 
 /*
__global__ void gaussianPass ( int patchSize , int dataSize , float * gaussFilter , float * data ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = blockDim . x * gridDim . x ; for ( int i = index ; i < dataSize ; i += stride ) { data [ i ] = gaussFilter [ i % ( patchSize * patchSize ) ] * data [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void gaussianPass(int patchSize, int dataSize, float* gaussFilter, float* data);

        int main() {
            // Test Case 1: dataSize equals patchSize*patchSize
            {
                const int patchSize = 2;
                const int dataSize = 4;
                float gaussFilter[4] = {0.1f, 0.2f, 0.3f, 0.4f};
                float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
                float expected[4] = {0.1f, 0.4f, 0.9f, 1.6f};
                
                gaussianPass(patchSize, dataSize, gaussFilter, data);
                
                for (int i = 0; i < dataSize; ++i) {
                    assert(fabs(data[i] - expected[i]) < 1e-6f);
                }
            }

            // Test Case 2: dataSize smaller than patchSize*patchSize
            {
                const int patchSize = 3;
                const int dataSize = 5;
                float gaussFilter[9] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};
                float data[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                float expected[5] = {0.1f, 0.4f, 0.9f, 1.6f, 2.5f};
                
                gaussianPass(patchSize, dataSize, gaussFilter, data);
                
                for (int i = 0; i < dataSize; ++i) {
                    assert(fabs(data[i] - expected[i]) < 1e-6f);
                }
            }

            // Test Case 3: dataSize larger than patchSize*patchSize (repeating pattern)
            {
                const int patchSize = 2;
                const int dataSize = 6;
                float gaussFilter[4] = {0.1f, 0.2f, 0.3f, 0.4f};
                float data[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float expected[6] = {0.1f, 0.4f, 0.9f, 1.6f, 0.5f, 1.2f};
                
                gaussianPass(patchSize, dataSize, gaussFilter, data);
                
                for (int i = 0; i < dataSize; ++i) {
                    assert(fabs(data[i] - expected[i]) < 1e-6f);
                }
            }

            // Test Case 4: minimum patchSize (1)
            {
                const int patchSize = 1;
                const int dataSize = 3;
                float gaussFilter[1] = {0.5f};
                float data[3] = {1.0f, 2.0f, 3.0f};
                float expected[3] = {0.5f, 1.0f, 1.5f};
                
                gaussianPass(patchSize, dataSize, gaussFilter, data);
                
                for (int i = 0; i < dataSize; ++i) {
                    assert(fabs(data[i] - expected[i]) < 1e-6f);
                }
            }

            // Test Case 5: empty data (should do nothing)
            {
                const int patchSize = 2;
                const int dataSize = 0;
                float gaussFilter[4] = {0.1f, 0.2f, 0.3f, 0.4f};
                float data[1] = {0.0f}; // dummy value
                
                gaussianPass(patchSize, dataSize, gaussFilter, data);
                // No assertion needed as it shouldn't modify anything
            }

            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }

        void gaussianPass(int patchSize, int dataSize, float* gaussFilter, float* data) {
            for (int i = 0; i < dataSize; ++i) {
                data[i] = gaussFilter[i % (patchSize * patchSize)] * data[i];
            }
        }