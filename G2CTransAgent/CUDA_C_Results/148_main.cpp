// original code(id = 148): 
 /*
__global__ void const_kernel ( int N , float ALPHA , float * X , int INCX ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) X [ i * INCX ] = ALPHA ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void const_kernel(int N, float ALPHA, float* X, int INCX) {
            for (int i = 0; i < N; ++i) {
                X[i * INCX] = ALPHA;
            }
        }

        void test_const_kernel() {
            // Test case 1: Basic functionality
            {
                float X[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                const_kernel(3, 10.0f, X, 1);
                assert(X[0] == 10.0f);
                assert(X[1] == 10.0f);
                assert(X[2] == 10.0f);
                assert(X[3] == 4.0f);
                assert(X[4] == 5.0f);
            }

            // Test case 2: Stride (INCX) greater than 1
            {
                float X[6] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                const_kernel(3, 20.0f, X, 2);
                assert(X[0] == 20.0f);
                assert(X[1] == 2.0f);
                assert(X[2] == 20.0f);
                assert(X[3] == 4.0f);
                assert(X[4] == 20.0f);
                assert(X[5] == 6.0f);
            }

            // Test case 3: N is zero (no elements to set)
            {
                float X[3] = {1.0f, 2.0f, 3.0f};
                const_kernel(0, 30.0f, X, 1);
                assert(X[0] == 1.0f);
                assert(X[1] == 2.0f);
                assert(X[2] == 3.0f);
            }

            // Test case 4: ALPHA is zero
            {
                float X[4] = {1.0f, 2.0f, 3.0f, 4.0f};
                const_kernel(4, 0.0f, X, 1);
                assert(X[0] == 0.0f);
                assert(X[1] == 0.0f);
                assert(X[2] == 0.0f);
                assert(X[3] == 0.0f);
            }

            // Test case 5: ALPHA is negative
            {
                float X[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                const_kernel(3, -5.0f, X, 1);
                assert(X[0] == -5.0f);
                assert(X[1] == -5.0f);
                assert(X[2] == -5.0f);
                assert(X[3] == 4.0f);
                assert(X[4] == 5.0f);
            }

            // Test case 6: INCX is zero (undefined behavior, but test for compilation)
            {
                float X[3] = {1.0f, 2.0f, 3.0f};
                const_kernel(3, 10.0f, X, 0);
                // No assertions, just testing for compilation
            }

            // Test case 7: INCX is negative (undefined behavior, but test for compilation)
            {
                float X[3] = {1.0f, 2.0f, 3.0f};
                const_kernel(3, 10.0f, X, -1);
                // No assertions, just testing for compilation
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_const_kernel();
            return 0;
        }