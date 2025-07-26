// Optimized code(id = 193): 

#include <iostream>

void mat_mul_kernel(int* m_A, int* m_B, int* m_C, int A_rows, int A_cols, int B_rows, int B_cols) {
    // Iterate over each element of the output matrix
    for (int row = 0; row < A_rows; ++row) {
        for (int col = 0; col < B_cols; ++col) {
            int sum = 0;
            // Compute the dot product of row from m_A and column from m_B
            for (int i = 0; i < A_cols; ++i) {
                sum += m_A[row * A_cols + i] * m_B[i * B_cols + col];
            }
            m_C[row * B_cols + col] = sum;
        }
    }
}

// Example usage (commented out as per requirements)
/*
int main() {
    // Example matrix dimensions
    const int A_rows = 3, A_cols = 2;
    const int B_rows = 2, B_cols = 3;
    
    // Example matrices
    int m_A[A_rows * A_cols] = {1, 2, 3, 4, 5, 6};
    int m_B[B_rows * B_cols] = {7, 8, 9, 10, 11, 12};
    int m_C[A_rows * B_cols] = {0};
    
    // Perform matrix multiplication
    mat_mul_kernel(m_A, m_B, m_C, A_rows, A_cols, B_rows, B_cols);
    
    // Print result
    for (int i = 0; i < A_rows; ++i) {
        for (int j = 0; j < B_cols; ++j) {
            std::cout << m_C[i * B_cols + j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
*/