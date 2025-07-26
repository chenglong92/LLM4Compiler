// original code(id = 26): 
 /*
__global__ void test ( float * input , const int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( tid == 0 ) { input [ tid ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void test(float* input, const int dims);

        int main() {
            // Test case 1: dims = 1, tid = 0
            {
                float input[1] = {1.0f};
                test(input, 1);
                assert(input[0] == 0.0f);
            }

            // Test case 2: dims > 1, tid = 0
            {
                const int dims = 5;
                float input[dims] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                test(input, dims);
                assert(input[0] == 0.0f);
                for (int i = 1; i < dims; ++i) {
                    assert(input[i] == static_cast<float>(i + 1));
                }
            }

            // Test case 3: dims = 0 (edge case)
            {
                float* input = nullptr;
                test(input, 0);
                // No assertion as function should handle dims=0 without issues
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }