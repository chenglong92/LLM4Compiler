// original code(id = 16): 
 /*
__global__ void cudaKernel_estimateSnr ( const float * corrSum , const int * corrValidCount , const float * maxval , float * snrValue , const int size ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx >= size ) return ; float mean = ( corrSum [ idx ] - maxval [ idx ] * maxval [ idx ] ) / ( corrValidCount [ idx ] - 1 ) ; snrValue [ idx ] = maxval [ idx ] * maxval [ idx ] / mean ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void estimateSnr(const float* corrSum, const int* corrValidCount, const float* maxval, float* snrValue, int size);

        int main() {
            // Test case 1: Basic test with positive values
            {
                const int size = 3;
                float corrSum[size] = {10.0f, 20.0f, 30.0f};
                int corrValidCount[size] = {5, 10, 15};
                float maxval[size] = {2.0f, 3.0f, 4.0f};
                float snrValue[size] = {0.0f, 0.0f, 0.0f};
                float expected[size] = {2.0f * 2.0f / ((10.0f - 4.0f) / (5 - 1)),
                                        3.0f * 3.0f / ((20.0f - 9.0f) / (10 - 1)),
                                        4.0f * 4.0f / ((30.0f - 16.0f) / (15 - 1))};

                estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);

                for (int i = 0; i < size; ++i) {
                    assert(fabs(snrValue[i] - expected[i]) < 1e-5f);
                }
            }

            // Test case 2: Edge case with single valid count (should be handled carefully in real implementation)
            {
                const int size = 2;
                float corrSum[size] = {5.0f, 8.0f};
                int corrValidCount[size] = {1, 2};
                float maxval[size] = {2.0f, 3.0f};
                float snrValue[size] = {0.0f, 0.0f};

                // Note: Division by zero may occur when corrValidCount is 1
                // This test case is to check how the function handles it
                estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);

                // No assertion here as behavior is undefined for corrValidCount <= 1
            }

            // Test case 3: Zero values
            {
                const int size = 2;
                float corrSum[size] = {0.0f, 0.0f};
                int corrValidCount[size] = {5, 10};
                float maxval[size] = {0.0f, 0.0f};
                float snrValue[size] = {0.0f, 0.0f};
                float expected[size] = {0.0f, 0.0f};

                estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);

                for (int i = 0; i < size; ++i) {
                    assert(snrValue[i] == expected[i]);
                }
            }

            // Test case 4: Negative values
            {
                const int size = 2;
                float corrSum[size] = {-10.0f, -20.0f};
                int corrValidCount[size] = {5, 10};
                float maxval[size] = {-2.0f, -3.0f};
                float snrValue[size] = {0.0f, 0.0f};
                float expected[size] = {4.0f / ((-10.0f - 4.0f) / (5 - 1)),
                                        9.0f / ((-20.0f - 9.0f) / (10 - 1))};

                estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);

                for (int i = 0; i < size; ++i) {
                    assert(fabs(snrValue[i] - expected[i]) < 1e-5f);
                }
            }

            // Test case 5: Large values
            {
                const int size = 2;
                float corrSum[size] = {1e6f, 2e6f};
                int corrValidCount[size] = {100, 200};
                float maxval[size] = {1e3f, 2e3f};
                float snrValue[size] = {0.0f, 0.0f};
                float expected[size] = {1e6f / ((1e6f - 1e6f) / (100 - 1)),
                                        4e6f / ((2e6f - 4e6f) / (200 - 1))};

                estimateSnr(corrSum, corrValidCount, maxval, snrValue, size);

                for (int i = 0; i < size; ++i) {
                    // Handle potential division by zero or infinity
                    if (isinf(expected[i]) || isnan(expected[i])) {
                        assert(isinf(snrValue[i]) || isnan(snrValue[i]));
                    } else {
                        assert(fabs(snrValue[i] - expected[i]) < 1e-5f);
                    }
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void estimateSnr(const float* corrSum, const int* corrValidCount, const float* maxval, float* snrValue, int size) {
            for (int idx = 0; idx < size; ++idx) {
                float mean = (corrSum[idx] - maxval[idx] * maxval[idx]) / (corrValidCount[idx] - 1);
                snrValue[idx] = maxval[idx] * maxval[idx] / mean;
            }
        }