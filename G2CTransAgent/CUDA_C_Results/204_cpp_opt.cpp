// Optimized code(id = 204): 

void castImageToUchar(float* deviceInputImageData, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize) {
    for (int w = 0; w < pixelSize; ++w) {
        ucharImage[w] = (unsigned char)(255 * deviceInputImageData[w]);
    }
}