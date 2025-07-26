// Optimized code(id = 194): 

void setOffset(int* offset, int dims, int batchSize) {
    offset[0] = 0;
    for (int i = 1; i < batchSize + 1; ++i) {
        offset[i] = i * dims;
    }
}