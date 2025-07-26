// Optimized code(id = 124): 

void primal_descent(float* y1, float* y2, float* xbar, float sigma, int w, int h, int nc) {
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    for (int z = 0; z < nc; ++z) {
                        int i = x + w * y + w * h * z;
                        float val = xbar[i];
                        float x1 = (x + 1 < w) ? (xbar[(x + 1) + w * y + w * h * z] - val) : 0.f;
                        float x2 = (y + 1 < h) ? (xbar[x + w * (y + 1) + w * h * z] - val) : 0.f;
                        x1 = y1[i] + sigma * x1;
                        x2 = y2[i] + sigma * x2;
                        float norm = sqrtf(x1 * x1 + x2 * x2);
                        y1[i] = x1 / fmax(1.f, norm);
                        y2[i] = x2 / fmax(1.f, norm);
                    }
                }
            }
        }