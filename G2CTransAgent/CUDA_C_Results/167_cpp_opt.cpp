// Optimized code(id = 167): 

void flipKernel(float* array1, int width) {
    for (int current_index = 0; current_index < width * width / 2; ++current_index) {
        int replace = (width - 1 - current_index / width) * width + current_index % width;
        float temp = array1[current_index];
        array1[current_index] = array1[replace];
        array1[replace] = temp;
    }
}