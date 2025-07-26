// original code(id = 20): 
 /*
__global__ void runFilterCuda ( float * I , float * Q , int samplesLength , float * filter , int filterLength , float * filtered_I , float * filtered_Q , int convLength ) { int sampleIndex = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( sampleIndex >= convLength ) return ; int index ; float sumI , sumQ ; sumI = 0 ; sumQ = 0 ; for ( int j = sampleIndex - filterLength + 1 ; j <= sampleIndex ; j ++ ) { index = sampleIndex - j ; if ( ( j < samplesLength ) && ( j >= 0 ) ) { sumI += filter [ index ] * I [ j ] ; sumQ += filter [ index ] * Q [ j ] ; } } filtered_I [ sampleIndex ] = sumI ; filtered_Q [ sampleIndex ] = sumQ ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void runFilterCuda(float* I, float* Q, int samplesLength, float* filter, int filterLength, float* filtered_I, float* filtered_Q, int convLength) {
            for (int sampleIndex = 0; sampleIndex < convLength; ++sampleIndex) {
                float sumI = 0.0f;
                float sumQ = 0.0f;
                
                for (int j = sampleIndex - filterLength + 1; j <= sampleIndex; ++j) {
                    int index = sampleIndex - j;
                    if (j >= 0 && j < samplesLength) {
                        sumI += filter[index] * I[j];
                        sumQ += filter[index] * Q[j];
                    }
                }
                
                filtered_I[sampleIndex] = sumI;
                filtered_Q[sampleIndex] = sumQ;
            }
        }

        void testNormalCase() {
            const int samplesLength = 1000;
            const int filterLength = 100;
            const int convLength = samplesLength + filterLength - 1;
            
            float I[samplesLength];
            float Q[samplesLength];
            float filter[filterLength];
            float filtered_I[convLength];
            float filtered_Q[convLength];
            
            for (int i = 0; i < samplesLength; ++i) {
                I[i] = static_cast<float>(i % 10);
                Q[i] = static_cast<float>((i + 5) % 10);
            }
            
            for (int i = 0; i < filterLength; ++i) {
                filter[i] = 1.0f / filterLength;
            }
            
            runFilterCuda(I, Q, samplesLength, filter, filterLength, filtered_I, filtered_Q, convLength);
            
            // Verify first element
            float expectedFirstI = I[0] * filter[0];
            float expectedFirstQ = Q[0] * filter[0];
            assert(filtered_I[0] == expectedFirstI);
            assert(filtered_Q[0] == expectedFirstQ);
            
            // Verify middle element
            float expectedMiddleI = 0.0f;
            float expectedMiddleQ = 0.0f;
            for (int i = 0; i < filterLength; ++i) {
                expectedMiddleI += I[500 - i] * filter[i];
                expectedMiddleQ += Q[500 - i] * filter[i];
            }
            assert(abs(filtered_I[500] - expectedMiddleI) < 0.0001f);
            assert(abs(filtered_Q[500] - expectedMiddleQ) < 0.0001f);
            
            std::cout << "Normal case test passed." << std::endl;
        }

        void testEdgeCaseEmptyInput() {
            const int samplesLength = 0;
            const int filterLength = 10;
            const int convLength = samplesLength + filterLength - 1;
            
            float I[1] = {0};
            float Q[1] = {0};
            float filter[filterLength];
            float filtered_I[convLength];
            float filtered_Q[convLength];
            
            for (int i = 0; i < filterLength; ++i) {
                filter[i] = 1.0f / filterLength;
            }
            
            runFilterCuda(I, Q, samplesLength, filter, filterLength, filtered_I, filtered_Q, convLength);
            
            for (int i = 0; i < convLength; ++i) {
                assert(filtered_I[i] == 0.0f);
                assert(filtered_Q[i] == 0.0f);
            }
            
            std::cout << "Edge case (empty input) test passed." << std::endl;
        }

        void testEdgeCaseSingleSample() {
            const int samplesLength = 1;
            const int filterLength = 1;
            const int convLength = samplesLength + filterLength - 1;
            
            float I[samplesLength] = {5.0f};
            float Q[samplesLength] = {3.0f};
            float filter[filterLength] = {0.5f};
            float filtered_I[convLength];
            float filtered_Q[convLength];
            
            runFilterCuda(I, Q, samplesLength, filter, filterLength, filtered_I, filtered_Q, convLength);
            
            assert(filtered_I[0] == 2.5f);
            assert(filtered_Q[0] == 1.5f);
            
            std::cout << "Edge case (single sample) test passed." << std::endl;
        }

        void testAbnormalCaseNegativeLengths() {
            const int samplesLength = -100;
            const int filterLength = -50;
            const int convLength = -149;
            
            float I[1] = {0};
            float Q[1] = {0};
            float filter[1] = {0};
            float filtered_I[1];
            float filtered_Q[1];
            
            // This should not crash, though behavior is undefined
            runFilterCuda(I, Q, samplesLength, filter, filterLength, filtered_I, filtered_Q, convLength);
            
            std::cout << "Abnormal case (negative lengths) test completed (no assertions)." << std::endl;
        }

        int main() {
            testNormalCase();
            testEdgeCaseEmptyInput();
            testEdgeCaseSingleSample();
            testAbnormalCaseNegativeLengths();
            
            std::cout << "All tests completed successfully." << std::endl;
            return 0;
        }