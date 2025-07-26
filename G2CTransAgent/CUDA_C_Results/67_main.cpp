// original code(id = 67): 
 /*
__global__ void fabsf_clamp_kernel ( int N , float * X , int INCX , float clamp_min , float clamp_max ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) { if ( X [ i * INCX ] >= 0 ) X [ i * INCX ] = fminf ( clamp_max , fmaxf ( clamp_min , X [ i * INCX ] ) ) ; else X [ i * INCX ] = fminf ( - clamp_min , fmaxf ( - clamp_max , X [ i * INCX ] ) ) ; } }
*/
// optimized code: 

#include <algorithm>
        #include <cmath>
        #include <cassert>
        #include <vector>
        #include <iostream>

        void fabsf_clamp_kernel(int N, float* X, int INCX, float clamp_min, float clamp_max) {
            for (int i = 0; i < N; ++i) {
                if (X[i * INCX] >= 0) {
                    X[i * INCX] = std::min(clamp_max, std::max(clamp_min, X[i * INCX]));
                } else {
                    X[i * INCX] = std::min(-clamp_min, std::max(-clamp_max, X[i * INCX]));
                }
            }
        }

        void test_fabsf_clamp_kernel() {
            // Test case 1: All positive values within range
            {
                std::vector<float> X = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                std::vector<float> expected = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 2: All negative values within range
            {
                std::vector<float> X = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};
                std::vector<float> expected = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 3: Mixed positive and negative values with some out of range
            {
                std::vector<float> X = {15.0f, -15.0f, 5.0f, -5.0f, 0.0f};
                std::vector<float> expected = {10.0f, -10.0f, 5.0f, -5.0f, 0.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 4: All values above positive clamp
            {
                std::vector<float> X = {11.0f, 12.0f, 13.0f, 14.0f, 15.0f};
                std::vector<float> expected = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 5: All values below negative clamp
            {
                std::vector<float> X = {-11.0f, -12.0f, -13.0f, -14.0f, -15.0f};
                std::vector<float> expected = {-10.0f, -10.0f, -10.0f, -10.0f, -10.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 6: Non-unit stride
            {
                std::vector<float> X = {1.0f, 0.0f, 2.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f, 5.0f};
                std::vector<float> expected = {1.0f, 0.0f, 2.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f, 5.0f};
                fabsf_clamp_kernel(5, X.data(), 2, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 7: Empty input
            {
                std::vector<float> X;
                std::vector<float> expected;
                fabsf_clamp_kernel(0, X.data(), 1, 0.0f, 10.0f);
                assert(X == expected);
            }

            // Test case 8: Clamp to zero
            {
                std::vector<float> X = {-1.0f, 0.0f, 1.0f};
                std::vector<float> expected = {0.0f, 0.0f, 0.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, 0.0f, 0.0f);
                assert(X == expected);
            }

            // Test case 9: Negative clamp values (should still work)
            {
                std::vector<float> X = {-5.0f, 0.0f, 5.0f};
                std::vector<float> expected = {-5.0f, 0.0f, 5.0f};
                fabsf_clamp_kernel(X.size(), X.data(), 1, -10.0f, 10.0f);
                assert(X == expected);
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_fabsf_clamp_kernel();
            return 0;
        }