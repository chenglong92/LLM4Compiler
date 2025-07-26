// original code(id = 23): 
 /*
__global__ void mul_Scalar_matrix ( float * a , float value , float * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] * value ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void mul_Scalar_matrix(float* a, float value, float* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] * value;
    }
}

int main() {
    // Test case 1: Basic multiplication
    {
        float a[] = {1.0f, 2.0f, 3.0f};
        float c[3];
        float value = 2.0f;
        mul_Scalar_matrix(a, value, c, 3);
        assert(c[0] == 2.0f);
        assert(c[1] == 4.0f);
        assert(c[2] == 6.0f);
    }

    // Test case 2: Multiplication with zero scalar
    {
        float a[] = {1.0f, 2.0f, 3.0f};
        float c[3];
        float value = 0.0f;
        mul_Scalar_matrix(a, value, c, 3);
        assert(c[0] == 0.0f);
        assert(c[1] == 0.0f);
        assert(c[2] == 0.0f);
    }

    // Test case 3: Multiplication with negative scalar
    {
        float a[] = {1.0f, -2.0f, 3.0f};
        float c[3];
        float value = -1.0f;
        mul_Scalar_matrix(a, value, c, 3);
        assert(c[0] == -1.0f);
        assert(c[1] == 2.0f);
        assert(c[2] == -3.0f);
    }

    // Test case 4: Empty matrix (N = 0)
    {
        float a[] = {1.0f, 2.0f, 3.0f};
        float c[3];
        float value = 5.0f;
        mul_Scalar_matrix(a, value, c, 0);
        // No assertions needed as function should handle N=0 without issues
    }

    // Test case 5: Large matrix
    {
        const int N = 1000;
        float a[N];
        float c[N];
        float value = 3.0f;
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<float>(i);
        }
        mul_Scalar_matrix(a, value, c, N);
        for (int i = 0; i < N; ++i) {
            assert(c[i] == static_cast<float>(i) * value);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}