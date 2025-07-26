// Optimized code(id = 18): 

void activate_array_leaky(float* x, int n) {
    for (int index = 0; index < n; ++index) {
        float val = x[index];
        x[index] = (val > 0) ? val : val / 10;
    }
}