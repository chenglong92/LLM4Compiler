// original code(id = 76): 
 /*
__global__ void gpu_matrix_mul ( int * a , int * b , int * c , int N ) { int row = blockIdx . y * blockDim . y + threadIdx . y ; int col = blockIdx . x * blockDim . x + threadIdx . x ; int sum = 0 ; if ( col < N && row < N ) { for ( int i = 0 ; i < N ; i ++ ) { sum += a [ row * N + i ] * b [ i * N + col ] ; } c [ row * N + col ] = sum ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void cpu_matrix_mul(int* a, int* b, int* c, int N) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            int sum = 0;
            for (int i = 0; i < N; ++i) {
                sum += a[row * N + i] * b[i * N + col];
            }
            c[row * N + col] = sum;
        }
    }
}

void print_matrix(int* matrix, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
}

void test_matrix_multiplication() {
    // Test case 1: 2x2 matrices
    {
        int N = 2;
        int a[] = {1, 2, 3, 4};
        int b[] = {5, 6, 7, 8};
        int c[4];
        int expected[] = {19, 22, 43, 50};

        cpu_matrix_mul(a, b, c, N);

        for (int i = 0; i < N * N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: 1x1 matrices
    {
        int N = 1;
        int a[] = {5};
        int b[] = {7};
        int c[1];
        int expected[] = {35};

        cpu_matrix_mul(a, b, c, N);

        assert(c[0] == expected[0]);
    }

    // Test case 3: 3x3 matrices with zeros
    {
        int N = 3;
        int a[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int c[9];
        int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        cpu_matrix_mul(a, b, c, N);

        for (int i = 0; i < N * N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: 2x2 matrices with negative numbers
    {
        int N = 2;
        int a[] = {-1, -2, -3, -4};
        int b[] = {-5, -6, -7, -8};
        int c[4];
        int expected[] = {19, 22, 43, 50};

        cpu_matrix_mul(a, b, c, N);

        for (int i = 0; i < N * N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: 3x3 identity matrix multiplication
    {
        int N = 3;
        int a[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        int b[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        int c[9];
        int expected[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};

        cpu_matrix_mul(a, b, c, N);

        for (int i = 0; i < N * N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_matrix_multiplication();
    return 0;
}