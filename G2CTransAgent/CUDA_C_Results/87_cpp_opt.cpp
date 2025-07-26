// Optimized code(id = 87): 

void cpu_matrix_transpose(int* mat_in, int* mat_out, unsigned int rows, unsigned int cols) {
    for (unsigned int idx = 0; idx < cols; ++idx) {
        for (unsigned int idy = 0; idy < rows; ++idy) {
            unsigned int pos = idy * cols + idx;
            unsigned int trans_pos = idx * rows + idy;
            mat_out[trans_pos] = mat_in[pos];
        }
    }
}