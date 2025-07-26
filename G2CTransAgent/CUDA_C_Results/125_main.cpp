// original code(id = 125): 
 /*
__global__ void doubleArrayElementwiseSquareKernel ( double * d_in , double * d_out , int length ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = pow ( d_in [ tid ] , 2 ) ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void doubleArrayElementwiseSquare(double* d_in, double* d_out, int length) {
            for (int tid = 0; tid < length; ++tid) {
                d_out[tid] = pow(d_in[tid], 2);
            }
        }

        int main() {
            // Test case 1: Basic test with positive numbers
            {
                double input[] = {1.0, 2.0, 3.0};
                double output[3];
                double expected[] = {1.0, 4.0, 9.0};
                doubleArrayElementwiseSquare(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 2: Test with negative numbers
            {
                double input[] = {-1.0, -2.0, -3.0};
                double output[3];
                double expected[] = {1.0, 4.0, 9.0};
                doubleArrayElementwiseSquare(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 3: Test with zero
            {
                double input[] = {0.0};
                double output[1];
                double expected[] = {0.0};
                doubleArrayElementwiseSquare(input, output, 1);
                assert(output[0] == expected[0]);
            }

            // Test case 4: Test with fractional numbers
            {
                double input[] = {0.5, 1.5, 2.5};
                double output[3];
                double expected[] = {0.25, 2.25, 6.25};
                doubleArrayElementwiseSquare(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 5: Test with large numbers
            {
                double input[] = {1e6, 2e6, 3e6};
                double output[3];
                double expected[] = {1e12, 4e12, 9e12};
                doubleArrayElementwiseSquare(input, output, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 6: Test with empty array (should handle gracefully)
            {
                double* input = nullptr;
                double* output = nullptr;
                doubleArrayElementwiseSquare(input, output, 0);
                // No assertion needed as the function should handle length=0
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }