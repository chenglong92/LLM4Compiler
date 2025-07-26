// Optimized code(id = 229): 

void conv2(float* A, float* kernel, int inputSize, int depth, int kernelSize, int stride, int pad, float* B, int outputSize) {
    for (int i = 0; i < outputSize; ++i) {
        for (int j = 0; j < outputSize; ++j) {
            int Ai = i * stride;
            int Aj = j * stride;
            int startk = (pad - Ai) < 0 ? 0 : pad - Ai;
            int endk = kernelSize < (inputSize + pad - Ai) ? kernelSize : (inputSize + pad - Ai);
            int startl = (pad - Aj) < 0 ? 0 : pad - Aj;
            int endl = kernelSize < (inputSize + pad - Aj) ? kernelSize : (inputSize + pad - Aj);
            
            for (int d = 0; d < depth; ++d) {
                float sum = 0;
                for (int k = startk; k < endk; ++k) {
                    for (int l = startl; l < endl; ++l) {
                        sum += A[d * inputSize * inputSize + (Ai + k - pad) * inputSize + Aj + l - pad] * 
                               kernel[d * kernelSize * kernelSize + k * kernelSize + l];
                    }
                }
                B[d * outputSize * outputSize + i * outputSize + j] = sum;
            }
        }
    }
}