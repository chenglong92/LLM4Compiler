// Optimized code(id = 199): 

void fill_idx(int N, int* device_input, int* device_output) {
    for (int idx = 0; idx < N - 1; ++idx) {
        if (device_input[idx] + 1 == device_input[idx + 1]) {
            device_output[device_input[idx]] = idx;
        }
    }
}