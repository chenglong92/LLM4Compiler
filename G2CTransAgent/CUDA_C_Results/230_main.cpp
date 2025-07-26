// original code(id = 230): 
 /*
__global__ void subtract_matrix ( float * a , float * b , float * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] - b [ idx ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void subtract_matrix(float* a, float* b, float* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] - b[idx];
    }
}

void test_subtract_matrix() {
    // Test case 1: Simple subtraction with positive numbers
    {
        float a[] = {5.0f, 3.0f, 10.0f};
        float b[] = {2.0f, 1.0f, 4.0f};
        float c[3];
        float expected[] = {3.0f, 2.0f, 6.0f};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Subtraction with negative numbers
    {
        float a[] = {-1.0f, -5.0f, -3.0f};
        float b[] = {-2.0f, -3.0f, -1.0f};
        float c[3];
        float expected[] = {1.0f, -2.0f, -2.0f};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 3: Subtraction with mixed positive and negative numbers
    {
        float a[] = {4.0f, -2.0f, 0.0f};
        float b[] = {1.0f, 3.0f, -5.0f};
        float c[3];
        float expected[] = {3.0f, -5.0f, 5.0f};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Single element arrays
    {
        float a[] = {7.5f};
        float b[] = {2.5f};
        float c[1];
        float expected[] = {5.0f};
        subtract_matrix(a, b, c, 1);
        assert(c[0] == expected[0]);
    }

    // Test case 5: Empty arrays (N = 0)
    {
        float a[] = {};
        float b[] = {};
        float c[0];
        subtract_matrix(a, b, c, 0);
        // No assertion needed as it should just not crash
    }

    // Test case 6: Large arrays
    {
        const int N = 1000;
        float a[N], b[N], c[N], expected[N];
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<float>(i);
            b[i] = static_cast<float>(i / 2);
            expected[i] = a[i] - b[i];
        }
        subtract_matrix(a, b, c, N);
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }
}

int main() {
    test_subtract_matrix();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}