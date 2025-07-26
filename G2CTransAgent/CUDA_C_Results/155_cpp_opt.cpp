// Optimized code(id = 155): 

void castImageToGrayScale(unsigned char* ucharImage, unsigned char* grayImage, int imageWidth, int imageHeight, int channels) {
    for (int h = 0; h < imageHeight; ++h) {
        for (int w = 0; w < imageWidth; ++w) {
            int idx = imageWidth * h + w;
            unsigned char r = ucharImage[idx * channels];
            unsigned char g = ucharImage[idx * channels + 1];
            unsigned char b = ucharImage[idx * channels + 2];
            grayImage[idx] = static_cast<unsigned char>(0.21f * r + 0.71f * g + 0.07f * b);
        }
    }
}