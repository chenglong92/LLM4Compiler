// Optimized code(id = 157): 

void Mul_half(float* src, float* dst) {
    for (int index = 0; index < 3; ++index) {
        dst[index] = src[index] * 0.5f;
    }
}