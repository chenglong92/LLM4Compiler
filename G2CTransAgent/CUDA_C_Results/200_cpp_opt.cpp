// Optimized code(id = 200): 

void vadd(const float* a, const float* b, float* c, const unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        c[i] = a[i] + b[i];
    }
}