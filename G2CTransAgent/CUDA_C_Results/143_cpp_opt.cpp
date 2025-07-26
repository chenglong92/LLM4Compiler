// Optimized code(id = 143): 

void subAvg(int* input, int count, int avg) {
    for (int index = 0; index < count; ++index) {
        input[index] = input[index] - avg;
    }
}