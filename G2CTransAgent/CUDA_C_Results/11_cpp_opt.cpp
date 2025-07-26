// Optimized code(id = 11): 

void testInt1(const int* input, int dims) {
    // Simulate thread behavior with a loop
    for (int tid = 0; tid < dims; tid++) {
        int sum = 0;  // Initialize sum to 0 for each "thread"
        for (int i = 0; i < 3000 * 4; i++) {
            if (input[i] == 0) {
                sum++;
            }
        }
        // sum is unused, just like in the original kernel
    }
}