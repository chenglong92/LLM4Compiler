// Optimized code(id = 10): 

void is_repeat(int N, int* device_input, int* device_output) {
    for (int idx = 0; idx < N; ++idx) {
        device_output[idx] = 0;
        if (idx + 1 < N && device_input[idx] == device_input[idx + 1]) {
            device_output[idx] = 1;
        }
    }
}