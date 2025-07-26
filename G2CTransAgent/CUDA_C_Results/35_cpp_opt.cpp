// Optimized code(id = 35): 

void rows_dc_offset_remove_layer(float* output, float* input, unsigned int width, unsigned int height, unsigned int depth) {
    for (unsigned int channel = 0; channel < depth; ++channel) {
        for (unsigned int row = 0; row < height; ++row) {
            for (unsigned int column = 0; column < width - 1; ++column) {
                unsigned int idx = (channel * height + row) * width + column;
                output[idx] = input[idx] - input[idx + 1];
            }
        }
    }
}