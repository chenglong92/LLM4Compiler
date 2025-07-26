// Optimized code(id = 130): 

void memcpy_kernel(int* dst, int* src, size_t n) {
    size_t num_elements = n / sizeof(int);
    for (size_t i = 0; i < num_elements; ++i) {
        dst[i] = src[i];
    }
}