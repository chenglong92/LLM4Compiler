// original code(id = 147): 
 /*
__global__ void doubleArrayScalarMultiplyKernel ( double * d_in , double * d_out , int length , double scalar ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in [ tid ] * scalar ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void doubleArrayScalarMultiply(double* d_in, double* d_out, int length, double scalar) {
            for (int i = 0; i < length; ++i) {
                d_out[i] = d_in[i] * scalar;
            }
        }

        int main() {
            // Test case 1: Basic test with positive scalar
            {
                double in[] = {1.0, 2.0, 3.0, 4.0};
                double out[4];
                double expected[] = {2.0, 4.0, 6.0, 8.0};
                double scalar = 2.0;
                doubleArrayScalarMultiply(in, out, 4, scalar);
                for (int i = 0; i < 4; ++i) {
                    assert(out[i] == expected[i]);
                }
            }

            // Test case 2: Negative scalar
            {
                double in[] = {1.0, 2.0, 3.0, 4.0};
                double out[4];
                double expected[] = {-1.0, -2.0, -3.0, -4.0};
                double scalar = -1.0;
                doubleArrayScalarMultiply(in, out, 4, scalar);
                for (int i = 0; i < 4; ++i) {
                    assert(out[i] == expected[i]);
                }
            }

            // Test case 3: Zero scalar
            {
                double in[] = {1.0, 2.0, 3.0, 4.0};
                double out[4];
                double expected[] = {0.0, 0.0, 0.0, 0.0};
                double scalar = 0.0;
                doubleArrayScalarMultiply(in, out, 4, scalar);
                for (int i = 0; i < 4; ++i) {
                    assert(out[i] == expected[i]);
                }
            }

            // Test case 4: Empty array
            {
                double in[] = {};
                double out[] = {};
                double scalar = 1.0;
                doubleArrayScalarMultiply(in, out, 0, scalar);
                // No assertion needed as the function should handle zero-length arrays
            }

            // Test case 5: Large array
            {
                const int length = 1000;
                double in[length];
                double out[length];
                double expected[length];
                double scalar = 3.5;
                for (int i = 0; i < length; ++i) {
                    in[i] = i;
                    expected[i] = i * scalar;
                }
                doubleArrayScalarMultiply(in, out, length, scalar);
                for (int i = 0; i < length; ++i) {
                    assert(out[i] == expected[i]);
                }
            }

            // Test case 6: Fractional scalar
            {
                double in[] = {1.0, 2.0, 3.0, 4.0};
                double out[4];
                double expected[] = {0.5, 1.0, 1.5, 2.0};
                double scalar = 0.5;
                doubleArrayScalarMultiply(in, out, 4, scalar);
                for (int i = 0; i < 4; ++i) {
                    assert(out[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }