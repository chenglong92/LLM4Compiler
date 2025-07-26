// original code(id = 201): 
 /*
__global__ void sumAndScale ( float * noiseVariance , float * diffMag2 , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i >= n ) return ; int batchJump = i * 347 ; float temp ; temp = 0 ; for ( int sumIndex = 0 ; sumIndex < 347 ; sumIndex ++ ) temp += diffMag2 [ batchJump + sumIndex ] ; temp = .00161812 * temp ; noiseVariance [ i ] = temp ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cstdlib>
        #include <ctime>

        void sumAndScale(float* noiseVariance, float* diffMag2, int n);

        int main() {
            // Test Case 1: Basic functionality test
            {
                const int n = 3;
                float noiseVariance[n] = {0};
                float diffMag2[n * 347];
                
                // Fill with simple pattern
                for (int i = 0; i < n * 347; ++i) {
                    diffMag2[i] = (i % 10) * 0.1f;
                }
                
                sumAndScale(noiseVariance, diffMag2, n);
                
                // Verify results
                bool passed = true;
                for (int i = 0; i < n; ++i) {
                    float expected = 0.0f;
                    for (int j = 0; j < 347; ++j) {
                        expected += diffMag2[i * 347 + j];
                    }
                    expected *= 0.00161812f;
                    
                    if (fabs(noiseVariance[i] - expected) > 1e-6f) {
                        passed = false;
                        break;
                    }
                }
                
                std::cout << "Test Case 1: Basic functionality - " << (passed ? "PASSED" : "FAILED") << std::endl;
            }

            // Test Case 2: Edge case with n = 0
            {
                float noiseVariance[1] = {123.456f};  // Should remain unchanged
                float diffMag2[347] = {0};
                
                sumAndScale(noiseVariance, diffMag2, 0);
                
                bool passed = (fabs(noiseVariance[0] - 123.456f) < 1e-6f);
                std::cout << "Test Case 2: n = 0 - " << (passed ? "PASSED" : "FAILED") << std::endl;
            }

            // Test Case 3: Single batch (n = 1)
            {
                const int n = 1;
                float noiseVariance[n] = {0};
                float diffMag2[347];
                
                // Fill with constant value
                for (int i = 0; i < 347; ++i) {
                    diffMag2[i] = 2.5f;
                }
                
                sumAndScale(noiseVariance, diffMag2, n);
                
                float expected = 347 * 2.5f * 0.00161812f;
                bool passed = (fabs(noiseVariance[0] - expected) < 1e-6f);
                
                std::cout << "Test Case 3: Single batch - " << (passed ? "PASSED" : "FAILED") << std::endl;
            }

            // Test Case 4: Large n and random values
            {
                const int n = 100;
                float noiseVariance[n] = {0};
                float diffMag2[n * 347];
                
                std::srand(std::time(0));
                for (int i = 0; i < n * 347; ++i) {
                    diffMag2[i] = static_cast<float>(std::rand()) / RAND_MAX * 100.0f;
                }
                
                sumAndScale(noiseVariance, diffMag2, n);
                
                bool passed = true;
                for (int i = 0; i < n; ++i) {
                    float expected = 0.0f;
                    for (int j = 0; j < 347; ++j) {
                        expected += diffMag2[i * 347 + j];
                    }
                    expected *= 0.00161812f;
                    
                    if (fabs(noiseVariance[i] - expected) > 1e-5f) {  // Slightly larger tolerance for floating point
                        passed = false;
                        break;
                    }
                }
                
                std::cout << "Test Case 4: Large n with random values - " << (passed ? "PASSED" : "FAILED") << std::endl;
            }

            // Test Case 5: Negative values in input
            {
                const int n = 2;
                float noiseVariance[n] = {0};
                float diffMag2[n * 347];
                
                // Fill with alternating positive and negative values
                for (int i = 0; i < n * 347; ++i) {
                    diffMag2[i] = (i % 2 == 0) ? 1.0f : -1.0f;
                }
                
                sumAndScale(noiseVariance, diffMag2, n);
                
                bool passed = true;
                for (int i = 0; i < n; ++i) {
                    float expected = 0.0f;
                    for (int j = 0; j < 347; ++j) {
                        expected += diffMag2[i * 347 + j];
                    }
                    expected *= 0.00161812f;
                    
                    if (fabs(noiseVariance[i] - expected) > 1e-6f) {
                        passed = false;
                        break;
                    }
                }
                
                std::cout << "Test Case 5: Negative values in input - " << (passed ? "PASSED" : "FAILED") << std::endl;
            }

            return 0;
        }

        void sumAndScale(float* noiseVariance, float* diffMag2, int n) {
            for (int i = 0; i < n; ++i) {
                int batchJump = i * 347;
                float temp = 0.0f;
                for (int sumIndex = 0; sumIndex < 347; ++sumIndex) {
                    temp += diffMag2[batchJump + sumIndex];
                }
                noiseVariance[i] = 0.00161812f * temp;
            }
        }