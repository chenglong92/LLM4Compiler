// Optimized code(id = 45): 

void set_sorting_offset(const int nrows, const int ncols, int* offsets) {
    for (int tid = 0; tid <= ncols; ++tid) {
        offsets[tid] = tid * nrows;
    }
}