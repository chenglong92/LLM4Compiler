// Optimized code(id = 166): 

void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width) {
    for (int ty = 0; ty < width; ++ty) {
        for (int tx = 0; tx < width; ++tx) {
            float pvalue = 0;
            for (int k = 0; k < width; ++k) {
                float Mdelement = Md[ty * width + k];
                float Ndelement = Nd[k * width + tx];  // Fixed index calculation
                pvalue += Mdelement * Ndelement;
            }
            Pd[ty * width + tx] = pvalue;
        }
    }
}