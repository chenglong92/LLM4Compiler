// original code(id = 193): 
 /*
__global__ void mat_mul_kernel ( int * m_A , int * m_B , int * m_C , int A_rows , int A_cols , int B_rows , int B_cols ) { int sum = 0 ; int row = threadIdx . y + blockIdx . y * blockDim . y ; int col = threadIdx . x + blockIdx . x * blockDim . x ; if ( row < A_rows && col < B_cols ) { for ( int i = 0 ; i < A_cols ; i ++ ) { sum += m_A [ row * A_cols + i ] * m_B [ i * B_cols + col ] ; } m_C [ row * B_cols + col ] = sum ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void mat_mul_kernel(int* m_A, int* m_B, int* m_C, int A_rows, int A_cols, int B_rows, int B_cols) {
    for (int row = 0; row < A_rows; ++row) {
        for (int col = 0; col < B_cols; ++col) {
            int sum = 0;
            for (int i = 0; i < A_cols; ++i) {
                sum += m_A[row * A_cols + i] * m_B[i * B_cols + col];
            }
            m_C[row * B_cols + col] = sum;
        }
    }
}

void print_matrix(int* matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Test Case 1: Basic 2x2 matrix multiplication
    {
        const int A_rows = 2, A_cols = 2;
        const int B_rows = 2, B_cols = 2;
        int m_A[A_rows * A_cols] = {1, 2, 3, 4};
        int m_B[B_rows * B_cols] = {5, 6, 7, 8};
        int m_C[A_rows * B_cols] = {0};
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        int expected[A_rows * B_cols] = {19, 22, 43, 50};
        for (int i = 0; i < A_rows * B_cols; ++i) {
            assert(m_C[i] == expected[i]);
        }
    }

    // Test Case 2: Rectangular matrices (3x2 * 2x3)
    {
        const int A_rows = 3, A_cols = 2;
        const int B_rows = 2, B_cols = 3;
        int m_A[A_rows * A_cols] = {1, 2, 3, 4, 5, 6};
        int m_B[B_rows * B_cols] = {7, 8, 9, 10, 11, 12};
        int m_C[A_rows * B_cols] = {0};
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        int expected[A_rows * B_cols] = {27, 30, 33, 61, 68, 75, 95, 106, 117};
        for (int i = 0; i < A_rows * B_cols; ++i) {
            assert(m_C[i] == expected[i]);
        }
    }

    // Test Case 3: Identity matrix multiplication
    {
        const int A_rows = 3, A_cols = 3;
        const int B_rows = 3, B_cols = 3;
        int m_A[A_rows * A_cols] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        int m_B[B_rows * B_cols] = {5, 6, 7, 8, 9, 10, 11, 12, 13};
        int m_C[A_rows * B_cols] = {0};
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        for (int i = 0; i < A_rows * B_cols; ++i) {
            assert(m_C[i] == m_B[i]);
        }
    }

    // Test Case 4: Zero matrix multiplication
    {
        const int A_rows = 2, A_cols = 3;
        const int B_rows = 3, B_cols = 2;
        int m_A[A_rows * A_cols] = {0};
        int m_B[B_rows * B_cols] = {1, 2, 3, 4, 5, 6};
        int m_C[A_rows * B_cols] = {0};
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        for (int i = 0; i < A_rows * B_cols; ++i) {
            assert(m_C[i] == 0);
        }
    }

    // Test Case 5: Single element matrices
    {
        const int A_rows = 1, A_cols = 1;
        const int B_rows = 1, B_cols = 1;
        int m_A[A_rows * A_cols] = {5};
        int m_B[B_rows * B_cols] = {7};
        int m_C[A_rows * B_cols] = {0};
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        assert(m_C[0] == 35);
    }

    // Test Case 6: Large matrices (stress test)
    {
        const int A_rows = 10, A_cols = 10;
        const int B_rows = 10, B_cols = 10;
        int m_A[A_rows * A_cols];
        int m_B[B_rows * B_cols];
        int m_C[A_rows * B_cols] = {0};
        
        // Fill matrices with sequential values
        for (int i = 0; i < A_rows * A_cols; ++i) {
            m_A[i] = i + 1;
            m_B[i] = i + 1;
        }
        
        mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
        
        // Verify first and last elements
        assert(m_C[0] == 3355);
        assert(m_C[A_rows * B_cols - 1] == 342100);
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}