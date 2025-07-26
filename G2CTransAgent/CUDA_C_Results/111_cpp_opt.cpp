// Optimized code(id = 111): 

void kernel(float* x, int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < 1000; j++) {
            sum += sqrt(pow(3.14159, i)) / float(j + 1);  // Added +1 to avoid division by zero
        }
        x[i] = sum;
    }
}