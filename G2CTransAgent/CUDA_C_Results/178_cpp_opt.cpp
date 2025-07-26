// Optimized code(id = 178): 

void SetToZero(float* d_vx, float* d_vy, float* d_vz, int w, int h, int l) {
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            unsigned int index = j * w + i;
            for (int k = 0; k < l; ++k, index += w * h) {
                d_vx[index] = 0;
                d_vy[index] = 0;
                d_vz[index] = 0;
            }
        }
    }
}