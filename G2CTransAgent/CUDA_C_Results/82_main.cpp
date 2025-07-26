// original code(id = 82): 
 /*
__global__ void fill_matrix ( double * const A , const int rows , const int cols ) { const int row = blockIdx . y * blockDim . y + threadIdx . y , col = blockIdx . x * blockDim . x + threadIdx . x ; if ( row < rows && col < cols ) { A [ row * cols + col ] = row ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void fill_matrix(double* const A, const int rows, const int cols) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            A[row * cols + col] = row;
        }
    }
}

void test_fill_matrix() {
    // Test case 1: 3x3 matrix
    {
        const int rows = 3;
        const int cols = 3;
        double A[rows * cols];
        fill_matrix(A, rows, cols);
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                assert(A[row * cols + col] == row);
            }
        }
    }

    // Test case 2: 1x1 matrix (edge case)
    {
        const int rows = 1;
        const int cols = 1;
        double A[rows * cols];
        fill_matrix(A, rows, cols);
        assert(A[0] == 0);
    }

    // Test case 3: 2x5 matrix (rectangular matrix)
    {
        const int rows = 2;
        const int cols = 5;
        double A[rows * cols];
        fill_matrix(A, rows, cols);
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                assert(A[row * cols + col] == row);
            }
        }
    }

    // Test case 4: 5x2 matrix (rectangular matrix)
    {
        const int rows = 5;
        const int cols = 2;
        double A[rows * cols];
        fill_matrix(A, rows, cols);
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                assert(A[row * cols + col] == row);
            }
        }
    }

    // Test case 5: 0x0 matrix (edge case)
    {
        const int rows = 0;
        const int cols = 0;
        double* A = nullptr;
        fill_matrix(A, rows, cols);
        // No assertion needed as function should handle this safely
    }

    // Test case 6: 1000x1000 matrix (large matrix)
    {
        const int rows = 1000;
        const int cols = 1000;
        double* A = new double[rows * cols];
        fill_matrix(A, rows, cols);
        
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                assert(A[row * cols + col] == row);
            }
        }
        delete[] A;
    }
}

int main() {
    test_fill_matrix();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}