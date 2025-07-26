// Optimized code(id = 82): 

void fill_matrix(double* const A, const int rows, const int cols) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            A[row * cols + col] = row;
        }
    }
}