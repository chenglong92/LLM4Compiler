// Optimized code(id = 135): 

void cudaRunComplexFilter(float* I, float* Q, int samplesLength, float* hr, float* hi, int filterLength, float* filtered_I, float* filtered_Q, int convLength) {
    for (int sampleIndex = 0; sampleIndex < convLength; ++sampleIndex) {
        float sumI = 0;
        float sumQ = 0;
        
        for (int j = sampleIndex - filterLength + 1; j <= sampleIndex; ++j) {
            int index = sampleIndex - j;
            if ((j < samplesLength) && (j >= 0)) {
                sumI += (I[j] * hr[index]) - (Q[j] * hi[index]);
                sumQ += (I[j] * hi[index]) + (Q[j] * hr[index]);
            }
        }
        
        filtered_I[sampleIndex] = sumI;
        filtered_Q[sampleIndex] = sumQ;
    }
}