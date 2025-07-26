// Optimized code(id = 78): 

void compute_array_square(float* array, float* outArray, int size) {
    for (int index = 0; index < size; ++index) {
        outArray[index] = array[index] * array[index];
    }
}