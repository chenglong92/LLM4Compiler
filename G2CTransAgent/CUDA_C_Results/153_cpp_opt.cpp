// Optimized code(id = 153): 

void castImageTofloat(float* deviceOutputImageData, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize) {
            for (int w = 0; w < pixelSize; ++w) {
                deviceOutputImageData[w] = static_cast<float>(ucharImage[w] / 255.0f);
            }
        }