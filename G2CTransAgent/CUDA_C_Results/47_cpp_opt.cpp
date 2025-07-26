// Optimized code(id = 47): 

void countRangesGlobal(int size, int* A, int* B) {
    for (int i = 0; i < size; ++i) {
        int x = A[i] / 100;
        B[x] += 1;
    }
}