// original code(id = 186): 
 /*
__global__ void doubleArraySignKernel ( double * d_in , double * d_out , int length ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = ( 0 < d_in [ tid ] ) - ( d_in [ tid ] < 0 ) ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void doubleArraySign(double* d_in, double* d_out, int length);

        int main() {
            // Test case 1: All positive numbers
            {
                double d_in[] = {1.0, 2.5, 3.7, 4.2};
                double d_out[4];
                double expected[] = {1.0, 1.0, 1.0, 1.0};
                int length = sizeof(d_in) / sizeof(d_in[0]);

                doubleArraySign(d_in, d_out, length);

                for (int i = 0; i < length; ++i) {
                    assert(d_out[i] == expected[i]);
                }
            }

            // Test case 2: All negative numbers
            {
                double d_in[] = {-1.0, -2.5, -3.7, -4.2};
                double d_out[4];
                double expected[] = {-1.0, -1.0, -1.0, -1.0};
                int length = sizeof(d_in) / sizeof(d_in[0]);

                doubleArraySign(d_in, d_out, length);

                for (int i = 0; i < length; ++i) {
                    assert(d_out[i] == expected[i]);
                }
            }

            // Test case 3: All zeros
            {
                double d_in[] = {0.0, 0.0, 0.0, 0.0};
                double d_out[4];
                double expected[] = {0.0, 0.0, 0.0, 0.0};
                int length = sizeof(d_in) / sizeof(d_in[0]);

                doubleArraySign(d_in, d_out, length);

                for (int i = 0; i < length; ++i) {
                    assert(d_out[i] == expected[i]);
                }
            }

            // Test case 4: Mixed positive, negative, and zero values
            {
                double d_in[] = {1.0, -2.5, 0.0, 3.7, -4.2, 0.0};
                double d_out[6];
                double expected[] = {1.0, -1.0, 0.0, 1.0, -1.0, 0.0};
                int length = sizeof(d_in) / sizeof(d_in[0]);

                doubleArraySign(d_in, d_out, length);

                for (int i = 0; i < length; ++i) {
                    assert(d_out[i] == expected[i]);
                }
            }

            // Test case 5: Edge cases with large positive and negative numbers
            {
                double d_in[] = {1.0e308, -1.0e308, 1.0e-308, -1.0e-308};
                double d_out[4];
                double expected[] = {1.0, -1.0, 1.0, -1.0};
                int length = sizeof(d_in) / sizeof(d_in[0]);

                doubleArraySign(d_in, d_out, length);

                for (int i = 0; i < length; ++i) {
                    assert(d_out[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void doubleArraySign(double* d_in, double* d_out, int length) {
            for (int tid = 0; tid < length; ++tid) {
                d_out[tid] = (0 < d_in[tid]) - (d_in[tid] < 0);
            }
        }