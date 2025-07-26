// Optimized code(id = 69): 

void transposeNaive(int* vector, int* transposed, int size) {
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            transposed[row + column * size] = vector[column + row * size];
        }
    }
}