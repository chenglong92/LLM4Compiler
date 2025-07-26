// original code(id = 228): 
 /*
__global__ void sigmoid_kernel ( float * input , float * output ) { int tid = threadIdx . x + blockIdx . x * blockDim . x ; output [ tid ] = 1 / ( 1 + expf ( - input [ tid ] ) ) ; }
*/
// optimized code: 

#include <cmath>
        #include <iostream>
        #include <cassert>

        void sigmoid_kernel(float* input, float* output, int size) {
            for (int tid = 0; tid < size; ++tid) {
                output[tid] = 1.0f / (1.0f + expf(-input[tid]));
            }
        }

        void test_sigmoid_kernel() {
            // Test case 1: Positive values
            {
                float input[] = {1.0f, 2.0f, 3.0f};
                float output[3];
                float expected[] = {0.731059f, 0.880797f, 0.952574f};
                sigmoid_kernel(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 2: Negative values
            {
                float input[] = {-1.0f, -2.0f, -3.0f};
                float output[3];
                float expected[] = {0.268941f, 0.119203f, 0.0474259f};
                sigmoid_kernel(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 3: Zero values
            {
                float input[] = {0.0f, 0.0f, 0.0f};
                float output[3];
                float expected[] = {0.5f, 0.5f, 0.5f};
                sigmoid_kernel(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 4: Mixed positive and negative values
            {
                float input[] = {-1.0f, 0.0f, 1.0f};
                float output[3];
                float expected[] = {0.268941f, 0.5f, 0.731059f};
                sigmoid_kernel(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 5: Large positive value
            {
                float input[] = {10.0f};
                float output[1];
                float expected[] = {0.999955f};
                sigmoid_kernel(input, output, 1);
                assert(fabs(output[0] - expected[0]) < 1e-6f);
            }

            // Test case 6: Large negative value
            {
                float input[] = {-10.0f};
                float output[1];
                float expected[] = {4.53979e-05f};
                sigmoid_kernel(input, output, 1);
                assert(fabs(output[0] - expected[0]) < 1e-6f);
            }

            // Test case 7: Empty array (should handle gracefully)
            {
                float* input = nullptr;
                float* output = nullptr;
                sigmoid_kernel(input, output, 0);
                // No assertion needed, just checking it doesn't crash
            }
        }

        int main() {
            test_sigmoid_kernel();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }