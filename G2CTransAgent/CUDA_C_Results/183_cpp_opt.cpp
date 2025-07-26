// Optimized code(id = 183): 

void matrixTranspose(int* in_mat, int* out_mat, int dim_rows, int dim_cols) {
            for (int row = 0; row < dim_rows; ++row) {
                for (int col = 0; col < dim_cols; ++col) {
                    unsigned int new_pos = col * dim_cols + row;
                    out_mat[new_pos] = in_mat[row * dim_cols + col];
                }
            }
        }