// original code(id = 216): 
 /*
__global__ void clip_kernel ( int N , float ALPHA , float * X , int INCX , float * Y , int INCY ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) { float val = X [ i * INCX ] ; Y [ i * INCY ] = val > ALPHA ? val : 0 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void clip_kernel(int N, float ALPHA, float* X, int INCX, float* Y, int INCY) {
    for (int i = 0; i < N; ++i) {
        float val = X[i * INCX];
        Y[i * INCY] = val > ALPHA ? val : 0;
    }
}

int main() {
    // Test case 1: All values in X are greater than ALPHA
    {
        int N = 5;
        float ALPHA = 0.5f;
        float X[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float Y[5];
        int INCX = 1;
        int INCY = 1;
        
        clip_kernel(N, ALPHA, X, INCX, Y, INCY);
        
        for (int i = 0; i < N; ++i) {
            assert(Y[i] == X[i]);
        }
    }

    // Test case 2: All values in X are less than ALPHA
    {
        int N = 5;
        float ALPHA = 6.0f;
        float X[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float Y[5];
        int INCX = 1;
        int INCY = 1;
        
        clip_kernel(N, ALPHA, X, INCX, Y, INCY);
        
        for (int i = 0; i < N; ++i) {
            assert(Y[i] == 0.0f);
        }
    }

    // Test case 3: Some values in X are greater than ALPHA, some are less
    {
        int N = 5;
        float ALPHA = 3.0f;
        float X[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        float expected[] = {0.0f, 0.0f, 0.0f, 4.0f, 5.0f};
        float Y[5];
        int INCX = 1;
        int INCY = 1;
        
        clip_kernel(N, ALPHA, X, INCX, Y, INCY);
        
        for (int i = 0; i < N; ++i) {
            assert(Y[i] == expected[i]);
        }
    }

    // Test case 4: INCX and INCY are not 1
    {
        int N = 3;
        float ALPHA = 2.0f;
        float X[] = {1.0f, 0.0f, 3.0f, 0.0f, 5.0f, 0.0f};
        float expected[] = {0.0f, 0.0f, 3.0f, 0.0f, 5.0f};
        float Y[5];
        int INCX = 2;
        int INCY = 1;
        
        clip_kernel(N, ALPHA, X, INCX, Y, INCY);
        
        for (int i = 0; i < N; ++i) {
            assert(Y[i] == expected[i]);
        }
    }

    // Test case 5: N is 0 (edge case)
    {
        int N = 0;
        float ALPHA = 1.0f;
        float X[] = {1.0f, 2.0f, 3.0f};
        float Y[3];
        int INCX = 1;
        int INCY = 1;
        
        clip_kernel(N, ALPHA, X, INCX, Y, INCY);
        // No assertions needed as N is 0
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}