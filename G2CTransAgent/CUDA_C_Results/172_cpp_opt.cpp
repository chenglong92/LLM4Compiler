// Optimized code(id = 172): 

void equalization(float* cdf, float* mincdf, unsigned char* ucharImage, int imageWidth, int imageHeight, int channels, int pixelSize) {
    for (int idx = 0; idx < pixelSize; ++idx) {
        unsigned char val = ucharImage[idx];
        float data = 255 * (cdf[val] - mincdf[0]) / (1 - mincdf[0]);
        if (data < 0.0f) data = 0.0f;
        else if (data > 255.0f) data = 255.0f;
        ucharImage[idx] = static_cast<unsigned char>(data);
    }
}