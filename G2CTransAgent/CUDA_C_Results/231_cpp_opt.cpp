// Optimized code(id = 231): 

#include <iostream>

void dual_ascent(float* xn, float* xbar, float* y1, float* y2, float* img, float tau, float lambda, float theta, int w, int h, int nc) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int z = 0; z < nc; ++z) {
                int i = x + w * y + w * h * z;
                float d1 = (x + 1 < w ? y1[i] : 0.f) - (x > 0 ? y1[(x - 1) + w * y + w * h * z] : 0.f);
                float d2 = (y + 1 < h ? y2[i] : 0.f) - (y > 0 ? y2[x + w * (y - 1) + w * h * z] : 0.f);
                float val = xn[i];
                xn[i] = ((val + tau * (d1 + d2)) + tau * lambda * img[i]) / (1.f + tau * lambda);
                xbar[i] = xn[i] + theta * (xn[i] - val);
            }
        }
    }
}

// Example usage (commented out):
/*
int main() {
    // Example parameters
    int w = 512, h = 512, nc = 3;
    float tau = 0.1f, lambda = 0.5f, theta = 1.0f;
    
    // Allocate memory
    float* xn = new float[w * h * nc];
    float* xbar = new float[w * h * nc];
    float* y1 = new float[w * h * nc];
    float* y2 = new float[w * h * nc];
    float* img = new float[w * h * nc];
    
    // Initialize arrays (example values)
    for (int i = 0; i < w * h * nc; ++i) {
        xn[i] = 0.0f;
        xbar[i] = 0.0f;
        y1[i] = 0.1f;
        y2[i] = 0.1f;
        img[i] = 0.5f;
    }
    
    // Call the function
    dual_ascent(xn, xbar, y1, y2, img, tau, lambda, theta, w, h, nc);
    
    // Clean up
    delete[] xn;
    delete[] xbar;
    delete[] y1;
    delete[] y2;
    delete[] img;
    
    return 0;
}
*/