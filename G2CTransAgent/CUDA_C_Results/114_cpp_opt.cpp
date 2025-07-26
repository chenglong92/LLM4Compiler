// Optimized code(id = 114): 

void pythagoras(unsigned char* a, unsigned char* b, unsigned char* c, int size) {
    for (int idx = 0; idx < size; ++idx) {
        float af = float(a[idx]);
        float bf = float(b[idx]);
        c[idx] = static_cast<unsigned char>(sqrtf(af * af + bf * bf));
    }
}