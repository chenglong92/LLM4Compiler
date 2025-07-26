// Optimized code(id = 61): 

void intMultiply(int* result, const int* val1, const int val2, const unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        result[i] = val1[i] * val2;
    }
}