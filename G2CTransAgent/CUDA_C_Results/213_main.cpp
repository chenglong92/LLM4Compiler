// original code(id = 213): 
 /*
__global__ void kernel_softmax ( float * x , int r , int c ) { unsigned int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i >= r ) return ; float temp1 = 0. , temp2 = 0. ; for ( int j = 0 ; j < c ; j ++ ) temp1 = max ( x [ i * c + j ] , temp1 ) ; for ( int j = 0 ; j < c ; j ++ ) { x [ i * c + j ] = expf ( x [ i * c + j ] - temp1 ) ; temp2 += x [ i * c + j ] ; } for ( int j = 0 ; j < c ; j ++ ) x [ i * c + j ] /= temp2 ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <algorithm>
        #include <vector>
        #include <cassert>

        void kernel_softmax(float* x, int r, int c);

        int main() {
            // Test case 1: Simple 2x2 matrix
            {
                float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float expected[] = {
                    expf(1.0f - 2.0f) / (expf(1.0f - 2.0f) + expf(2.0f - 2.0f)),
                    expf(2.0f - 2.0f) / (expf(1.0f - 2.0f) + expf(2.0f - 2.0f)),
                    expf(3.0f - 4.0f) / (expf(3.0f - 4.0f) + expf(4.0f - 4.0f)),
                    expf(4.0f - 4.0f) / (expf(3.0f - 4.0f) + expf(4.0f - 4.0f))
                };
                kernel_softmax(input, 2, 2);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(input[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 2: Single row with negative values
            {
                float input[] = {-1.0f, -2.0f, -3.0f};
                float expected[] = {
                    expf(-1.0f - -1.0f) / (expf(-1.0f - -1.0f) + expf(-2.0f - -1.0f) + expf(-3.0f - -1.0f)),
                    expf(-2.0f - -1.0f) / (expf(-1.0f - -1.0f) + expf(-2.0f - -1.0f) + expf(-3.0f - -1.0f)),
                    expf(-3.0f - -1.0f) / (expf(-1.0f - -1.0f) + expf(-2.0f - -1.0f) + expf(-3.0f - -1.0f))
                };
                kernel_softmax(input, 1, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(input[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 3: Large values (testing numerical stability)
            {
                float input[] = {1000.0f, 1001.0f, 1002.0f};
                float expected[] = {
                    expf(1000.0f - 1002.0f) / (expf(1000.0f - 1002.0f) + expf(1001.0f - 1002.0f) + expf(1002.0f - 1002.0f)),
                    expf(1001.0f - 1002.0f) / (expf(1000.0f - 1002.0f) + expf(1001.0f - 1002.0f) + expf(1002.0f - 1002.0f)),
                    expf(1002.0f - 1002.0f) / (expf(1000.0f - 1002.0f) + expf(1001.0f - 1002.0f) + expf(1002.0f - 1002.0f))
                };
                kernel_softmax(input, 1, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(fabs(input[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 4: Single element matrix
            {
                float input[] = {5.0f};
                float expected[] = {1.0f};
                kernel_softmax(input, 1, 1);
                assert(fabs(input[0] - expected[0]) < 1e-6f);
            }

            // Test case 5: All elements equal
            {
                float input[] = {3.0f, 3.0f, 3.0f, 3.0f};
                float expected[] = {0.25f, 0.25f, 0.25f, 0.25f};
                kernel_softmax(input, 2, 2);
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(input[i] - expected[i]) < 1e-6f);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }