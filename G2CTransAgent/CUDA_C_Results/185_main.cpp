// original code(id = 185): 
 /*
__global__ void boxesScale ( const float * input , float * output , int dims , float scale0 , float scale1 , float scale2 , float scale3 ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } output [ tid * 4 ] = input [ tid * 4 ] / scale0 ; output [ tid * 4 + 1 ] = input [ tid * 4 + 1 ] / scale1 ; output [ tid * 4 + 2 ] = input [ tid * 4 + 2 ] / scale2 ; output [ tid * 4 + 3 ] = input [ tid * 4 + 3 ] / scale3 ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void boxesScale(const float* input, float* output, int dims, float scale0, float scale1, float scale2, float scale3);

        int main() {
            // Test case 1: Single box with all scales set to 1.0f (no scaling)
            {
                const int dims = 1;
                float input[dims * 4] = {1.0f, 2.0f, 3.0f, 4.0f};
                float output[dims * 4];
                float expected[dims * 4] = {1.0f, 2.0f, 3.0f, 4.0f};
                
                boxesScale(input, output, dims, 1.0f, 1.0f, 1.0f, 1.0f);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 2: Single box with different scales for each dimension
            {
                const int dims = 1;
                float input[dims * 4] = {10.0f, 20.0f, 30.0f, 40.0f};
                float output[dims * 4];
                float expected[dims * 4] = {2.0f, 5.0f, 6.0f, 10.0f};
                
                boxesScale(input, output, dims, 5.0f, 4.0f, 5.0f, 4.0f);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 3: Multiple boxes with uniform scaling
            {
                const int dims = 3;
                float input[dims * 4] = {
                    1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f
                };
                float output[dims * 4];
                float expected[dims * 4] = {
                    0.5f, 1.0f, 1.5f, 2.0f,
                    2.5f, 3.0f, 3.5f, 4.0f,
                    4.5f, 5.0f, 5.5f, 6.0f
                };
                
                boxesScale(input, output, dims, 2.0f, 2.0f, 2.0f, 2.0f);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 4: Edge case with zero scales (division by zero should be handled by caller)
            {
                const int dims = 1;
                float input[dims * 4] = {1.0f, 2.0f, 3.0f, 4.0f};
                float output[dims * 4];
                
                // Note: This test case expects the function to perform division by zero.
                // In a real scenario, the caller should ensure scales are not zero.
                boxesScale(input, output, dims, 0.0f, 1.0f, 1.0f, 1.0f);
                
                // The behavior is undefined, so no assertions are made here.
            }

            // Test case 5: Large number of boxes with varying scales
            {
                const int dims = 1000;
                float input[dims * 4];
                float output[dims * 4];
                float expected[dims * 4];
                
                for (int i = 0; i < dims; ++i) {
                    input[i * 4] = i * 1.0f;
                    input[i * 4 + 1] = i * 2.0f;
                    input[i * 4 + 2] = i * 3.0f;
                    input[i * 4 + 3] = i * 4.0f;
                    
                    expected[i * 4] = (i * 1.0f) / 2.0f;
                    expected[i * 4 + 1] = (i * 2.0f) / 4.0f;
                    expected[i * 4 + 2] = (i * 3.0f) / 6.0f;
                    expected[i * 4 + 3] = (i * 4.0f) / 8.0f;
                }
                
                boxesScale(input, output, dims, 2.0f, 4.0f, 6.0f, 8.0f);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }