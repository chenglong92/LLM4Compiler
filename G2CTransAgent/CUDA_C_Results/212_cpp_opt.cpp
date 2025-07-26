// Optimized code(id = 212): 

void set_offset(int stride, int size, int* output) {
    for (int i = 0; i < size; ++i) {
        output[i] = i * stride;
    }
}