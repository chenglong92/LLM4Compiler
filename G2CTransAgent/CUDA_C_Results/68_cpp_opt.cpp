// Optimized code(id = 68): 

void grayscale(unsigned char* input, unsigned char* output, int size) {
    for (int i = 0; i < size; ++i) {
        unsigned char r = input[3 * i];
        unsigned char g = input[3 * i + 1];
        unsigned char b = input[3 * i + 2];
        output[i] = static_cast<unsigned char>(0.21f * r + 0.71f * g + 0.07f * b);
    }
}