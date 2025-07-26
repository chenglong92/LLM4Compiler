// original code(id = 207): 
 /*
__global__ void clamp_kernel ( int N , float * X , int INCX , float clamp_min , float clamp_max ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) X [ i * INCX ] = fminf ( clamp_max , fmaxf ( clamp_min , X [ i * INCX ] ) ) ; }
*/
// optimized code: 

#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>

void clamp_kernel(int N, float* X, int INCX, float clamp_min, float clamp_max);

int main() {
    // Test case 1: Basic clamping with INCX = 1
    {
        std::vector<float> X = {1.0f, -2.0f, 3.0f, -4.0f, 5.0f};
        std::vector<float> expected = {1.0f, -1.0f, 2.0f, -1.0f, 2.0f};
        clamp_kernel(5, X.data(), 1, -1.0f, 2.0f);
        assert(X == expected);
    }

    // Test case 2: Clamping with INCX = 2 (every other element)
    {
        std::vector<float> X = {1.0f, -1.0f, 3.0f, -3.0f, 5.0f, -5.0f, 7.0f, -7.0f};
        std::vector<float> expected = {1.0f, -1.0f, 0.5f, -3.0f, 0.5f, -5.0f, 0.5f, -7.0f};
        clamp_kernel(4, X.data(), 2, -0.5f, 0.5f);
        assert(X == expected);
    }

    // Test case 3: All values below clamp_min
    {
        std::vector<float> X = {-5.0f, -6.0f, -7.0f};
        std::vector<float> expected = {0.0f, 0.0f, 0.0f};
        clamp_kernel(3, X.data(), 1, 0.0f, 10.0f);
        assert(X == expected);
    }

    // Test case 4: All values above clamp_max
    {
        std::vector<float> X = {15.0f, 16.0f, 17.0f};
        std::vector<float> expected = {10.0f, 10.0f, 10.0f};
        clamp_kernel(3, X.data(), 1, 0.0f, 10.0f);
        assert(X == expected);
    }

    // Test case 5: Empty array
    {
        std::vector<float> X;
        std::vector<float> expected;
        clamp_kernel(0, X.data(), 1, -1.0f, 1.0f);
        assert(X == expected);
    }

    // Test case 6: Single element
    {
        std::vector<float> X = {42.0f};
        std::vector<float> expected = {10.0f};
        clamp_kernel(1, X.data(), 1, -10.0f, 10.0f);
        assert(X == expected);
    }

    // Test case 7: Large INCX
    {
        std::vector<float> X(100, 5.0f);
        X[0] = -10.0f;
        X[99] = 10.0f;
        clamp_kernel(2, X.data(), 99, -5.0f, 5.0f);
        assert(X[0] == -5.0f);
        assert(X[99] == 5.0f);
        for (int i = 1; i < 99; ++i) {
            assert(X[i] == 5.0f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void clamp_kernel(int N, float* X, int INCX, float clamp_min, float clamp_max) {
    for (int i = 0; i < N; ++i) {
        X[i * INCX] = std::min(clamp_max, std::max(clamp_min, X[i * INCX]));
    }
}