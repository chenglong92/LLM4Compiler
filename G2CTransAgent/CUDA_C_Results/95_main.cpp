// original code(id = 95): 
 /*
__global__ void LreluBackward ( float * srcDiff , float * dstDiff , float * srcData , int data_size , float alpha ) { int thread_index = threadIdx . x + blockIdx . x * blockDim . x ; int num_threads = blockDim . x * gridDim . x ; for ( int i = 0 ; i < data_size ; i += num_threads ) { int index = i + thread_index ; if ( index < data_size ) { dstDiff [ index ] = srcDiff [ index ] * ( ( srcData [ index ] > 0 ) + ( srcData [ index ] <= 0 ) * alpha ) ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void LreluBackward(float* srcDiff, float* dstDiff, float* srcData, int data_size, float alpha) {
            for (int i = 0; i < data_size; ++i) {
                dstDiff[i] = srcDiff[i] * ((srcData[i] > 0) + (srcData[i] <= 0) * alpha);
            }
        }

        void test_LreluBackward() {
            // Test case 1: All positive values
            {
                const int size = 3;
                float srcDiff[size] = {1.0f, 2.0f, 3.0f};
                float srcData[size] = {0.5f, 1.0f, 2.0f};
                float dstDiff[size] = {0};
                float expected[size] = {1.0f, 2.0f, 3.0f};
                float alpha = 0.1f;
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                
                for (int i = 0; i < size; ++i) {
                    assert(fabs(dstDiff[i] - expected[i]) < 1e-6f);
                }
            }
            
            // Test case 2: All negative values
            {
                const int size = 3;
                float srcDiff[size] = {1.0f, 2.0f, 3.0f};
                float srcData[size] = {-0.5f, -1.0f, -2.0f};
                float dstDiff[size] = {0};
                float expected[size] = {0.1f, 0.2f, 0.3f};
                float alpha = 0.1f;
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                
                for (int i = 0; i < size; ++i) {
                    assert(fabs(dstDiff[i] - expected[i]) < 1e-6f);
                }
            }
            
            // Test case 3: Mixed positive, negative and zero values
            {
                const int size = 5;
                float srcDiff[size] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                float srcData[size] = {1.0f, -1.0f, 0.0f, 0.5f, -0.5f};
                float dstDiff[size] = {0};
                float expected[size] = {1.0f, 0.2f, 0.3f, 4.0f, 0.5f};
                float alpha = 0.1f;
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                
                for (int i = 0; i < size; ++i) {
                    assert(fabs(dstDiff[i] - expected[i]) < 1e-6f);
                }
            }
            
            // Test case 4: Different alpha value
            {
                const int size = 3;
                float srcDiff[size] = {1.0f, 2.0f, 3.0f};
                float srcData[size] = {1.0f, -1.0f, 0.0f};
                float dstDiff[size] = {0};
                float expected[size] = {1.0f, 1.0f, 1.5f};
                float alpha = 0.5f;
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                
                for (int i = 0; i < size; ++i) {
                    assert(fabs(dstDiff[i] - expected[i]) < 1e-6f);
                }
            }
            
            // Test case 5: Empty array
            {
                const int size = 0;
                float* srcDiff = nullptr;
                float* srcData = nullptr;
                float* dstDiff = nullptr;
                float alpha = 0.1f;
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                // Should not crash
            }
            
            // Test case 6: Large array
            {
                const int size = 1000;
                float srcDiff[size];
                float srcData[size];
                float dstDiff[size];
                float expected[size];
                float alpha = 0.1f;
                
                for (int i = 0; i < size; ++i) {
                    srcDiff[i] = (i % 10) * 0.1f;
                    srcData[i] = (i % 2 == 0) ? i * 0.1f : -i * 0.1f;
                    expected[i] = (i % 2 == 0) ? srcDiff[i] : srcDiff[i] * alpha;
                }
                
                LreluBackward(srcDiff, dstDiff, srcData, size, alpha);
                
                for (int i = 0; i < size; ++i) {
                    assert(fabs(dstDiff[i] - expected[i]) < 1e-6f);
                }
            }
        }

        int main() {
            test_LreluBackward();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }