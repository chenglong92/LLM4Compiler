// Optimized code(id = 44): 

void get_ev(double* old_arr, double* new_arr, int size) {
    for (int tid = 0; tid < size; ++tid) {
        new_arr[tid] = old_arr[tid];
    }
}