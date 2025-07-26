// Optimized code(id = 96): 

#include <iostream>

void matrixMultiplication(int* dev_a, int* dev_b, int* dev_c, int row_a, int col_a, int col_b) {
    // Calculate the total number of elements in the output matrix
    int total_rows = row_a;
    int total_cols = col_b;
    
    // Iterate through each element of the output matrix
    for (int row = 0; row < total_rows; ++row) {
        for (int col = 0; col < total_cols; ++col) {
            int ret = 0;
            // Compute the dot product of row from dev_a and column from dev_b
            for (int i = 0; i < col_a; ++i) {
                ret += dev_a[row * col_a + i] * dev_b[i * col_b + col];
            }
            // Store the result in the output matrix
            dev_c[row * col_b + col] = ret;
        }
    }
}

// Example usage (commented out):
/*
int main() {
    // Example matrix dimensions
    int row_a = 3, col_a = 2, col_b = 3;
    
    // Example input matrices
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {7, 8, 9, 10, 11, 12};
    int c[row_a * col_b];
    
    matrixMultiplication(a, b, c, row_a, col_a, col_b);
    
    // Print result
    for (int i = 0; i < row_a; ++i) {
        for (int j = 0; j < col_b; ++j) {
            std::cout << c[i * col_b + j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
*/