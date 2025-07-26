// original code(id = 25): 
 /*
__global__ void dsubtract_matrix ( double * a , double * b , double * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] - b [ idx ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void subtract_matrix(double* a, double* b, double* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] - b[idx];
    }
}

void test_subtract_matrix() {
    // Test case 1: Simple subtraction with positive numbers
    {
        double a[] = {1.0, 2.0, 3.0};
        double b[] = {0.5, 1.5, 2.5};
        double c[3];
        double expected[] = {0.5, 0.5, 0.5};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Subtraction with negative numbers
    {
        double a[] = {-1.0, -2.0, -3.0};
        double b[] = {-0.5, -1.5, -2.5};
        double c[3];
        double expected[] = {-0.5, -0.5, -0.5};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 3: Subtraction with mixed positive and negative numbers
    {
        double a[] = {1.0, -2.0, 3.0};
        double b[] = {0.5, -1.5, 2.5};
        double c[3];
        double expected[] = {0.5, -0.5, 0.5};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Subtraction with zero
    {
        double a[] = {0.0, 0.0, 0.0};
        double b[] = {0.0, 0.0, 0.0};
        double c[3];
        double expected[] = {0.0, 0.0, 0.0};
        subtract_matrix(a, b, c, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: Single element subtraction
    {
        double a[] = {5.0};
        double b[] = {3.0};
        double c[1];
        double expected[] = {2.0};
        subtract_matrix(a, b, c, 1);
        assert(c[0] == expected[0]);
    }

    // Test case 6: Large matrix subtraction
    {
        const int N = 1000;
        double a[N], b[N], c[N], expected[N];
        for (int i = 0; i < N; ++i) {
            a[i] = i * 1.5;
            b[i] = i * 0.5;
            expected[i] = i * 1.0;
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