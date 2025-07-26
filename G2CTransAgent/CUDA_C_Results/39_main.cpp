// original code(id = 39): 
 /*
__global__ void LreluForward ( float * srcData , float * dstData , int data_size , float alpha ) { int thread_index = threadIdx . x + blockIdx . x * blockDim . x ; int num_threads = blockDim . x * gridDim . x ; for ( int i = 0 ; i < data_size ; i += num_threads ) { int index = i + thread_index ; if ( index < data_size ) { dstData [ index ] = srcData [ index ] > 0 ? srcData [ index ] : srcData [ index ] * alpha ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void LreluForward(float* srcData, float* dstData, int data_size, float alpha) {
            for (int index = 0; index < data_size; ++index) {
                dstData[index] = srcData[index] > 0 ? srcData[index] : srcData[index] * alpha;
            }
        }

        void test_LreluForward() {
            // Test case 1: All positive values
            {
                float src[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float dst[4];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
                LreluForward(src, dst, 4, 0.1f);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(dst[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 2: All negative values
            {
                float src[] = {-1.0f, -2.0f, -3.0f, -4.0f};
                float dst[4];
                float expected[] = {-0.1f, -0.2f, -0.3f, -0.4f};
                LreluForward(src, dst, 4, 0.1f);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(dst[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 3: Mixed positive and negative values
            {
                float src[] = {-1.5f, 2.0f, 0.0f, -3.0f, 4.0f};
                float dst[5];
                float expected[] = {-0.15f, 2.0f, 0.0f, -0.3f, 4.0f};
                LreluForward(src, dst, 5, 0.1f);
                for (int i = 0; i < 5; ++i) {
                    assert(fabs(dst[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 4: Zero alpha
            {
                float src[] = {-1.0f, 1.0f, -2.0f, 2.0f};
                float dst[4];
                float expected[] = {0.0f, 1.0f, 0.0f, 2.0f};
                LreluForward(src, dst, 4, 0.0f);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(dst[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 5: Alpha greater than 1
            {
                float src[] = {-1.0f, 1.0f, -2.0f, 2.0f};
                float dst[4];
                float expected[] = {-2.0f, 1.0f, -4.0f, 2.0f};
                LreluForward(src, dst, 4, 2.0f);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(dst[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 6: Empty array
            {
                float src[] = {};
                float dst[0];
                LreluForward(src, dst, 0, 0.1f);
                // No assertion needed as the function should handle size 0
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_LreluForward();
            return 0;
        }