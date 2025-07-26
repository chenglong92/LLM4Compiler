// Optimized code(id = 219): 

void downsampleCuda(float* I, float* Q, unsigned int numDownsampledSamples, float* downsampled_I, float* downsampled_Q, unsigned int factor) {
    for (unsigned int sampleIndex = 0; sampleIndex < numDownsampledSamples; ++sampleIndex) {
        unsigned int absoluteIndex = sampleIndex * factor;
        downsampled_I[sampleIndex] = I[absoluteIndex];
        downsampled_Q[sampleIndex] = Q[absoluteIndex];
    }
}