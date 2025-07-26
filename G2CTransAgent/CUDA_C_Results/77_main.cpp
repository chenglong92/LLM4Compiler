// original code(id = 77): 
 /*
__global__ void pow_kernel ( int N , float ALPHA , float * X , int INCX , float * Y , int INCY ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) Y [ i * INCY ] = pow ( X [ i * INCX ] , ALPHA ) ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void pow_kernel(int N, float ALPHA, float* X, int INCX, float* Y, int INCY);

        int main() {
            // Test case 1: Simple case with N=3, ALPHA=2.0, INCX=1, INCY=1
            {
                int N = 3;
                float ALPHA = 2.0f;
                float X[] = {1.0f, 2.0f, 3.0f};
                float Y[3];
                int INCX = 1;
                int INCY = 1;

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                assert(fabs(Y[0] - 1.0f) < 1e-6);
                assert(fabs(Y[1] - 4.0f) < 1e-6);
                assert(fabs(Y[2] - 9.0f) < 1e-6);
            }

            // Test case 2: Different increments (INCX=2, INCY=3)
            {
                int N = 2;
                float ALPHA = 3.0f;
                float X[] = {1.0f, 0.0f, 2.0f, 0.0f, 0.0f}; // Only elements 0 and 2 are used
                float Y[6] = {0.0f}; // Only elements 0 and 3 will be written
                int INCX = 2;
                int INCY = 3;

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                assert(fabs(Y[0] - 1.0f) < 1e-6);
                assert(fabs(Y[3] - 8.0f) < 1e-6);
                assert(fabs(Y[1]) < 1e-6); // Should remain unchanged
                assert(fabs(Y[2]) < 1e-6); // Should remain unchanged
            }

            // Test case 3: Zero elements (N=0)
            {
                int N = 0;
                float ALPHA = 1.5f;
                float X[] = {1.0f, 2.0f};
                float Y[2] = {0.0f};
                int INCX = 1;
                int INCY = 1;

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                assert(fabs(Y[0]) < 1e-6); // Should remain unchanged
                assert(fabs(Y[1]) < 1e-6); // Should remain unchanged
            }

            // Test case 4: Negative ALPHA
            {
                int N = 2;
                float ALPHA = -1.0f;
                float X[] = {1.0f, 2.0f};
                float Y[2];
                int INCX = 1;
                int INCY = 1;

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                assert(fabs(Y[0] - 1.0f) < 1e-6);
                assert(fabs(Y[1] - 0.5f) < 1e-6);
            }

            // Test case 5: Fractional ALPHA
            {
                int N = 2;
                float ALPHA = 0.5f;
                float X[] = {4.0f, 9.0f};
                float Y[2];
                int INCX = 1;
                int INCY = 1;

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                assert(fabs(Y[0] - 2.0f) < 1e-6);
                assert(fabs(Y[1] - 3.0f) < 1e-6);
            }

            // Test case 6: Large N
            {
                const int N = 1000;
                float ALPHA = 2.0f;
                float X[N];
                float Y[N];
                int INCX = 1;
                int INCY = 1;

                for (int i = 0; i < N; ++i) {
                    X[i] = i + 1.0f;
                }

                pow_kernel(N, ALPHA, X, INCX, Y, INCY);

                for (int i = 0; i < N; ++i) {
                    assert(fabs(Y[i] - pow(X[i], ALPHA)) < 1e-6);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }