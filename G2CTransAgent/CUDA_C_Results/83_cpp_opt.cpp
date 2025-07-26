// Optimized code(id = 83): 

void convertEdgeMaskToFloat(float* d_output, unsigned char* d_input, unsigned int width, unsigned int height) {
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            d_output[y * width + x] = std::min(
                static_cast<float>(d_input[y * width + x]),
                static_cast<float>(d_input[width * height + y * width + x])
            );
        }
    }
}