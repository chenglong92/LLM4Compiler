// Optimized code(id = 95): 

void LreluBackward(float* srcDiff, float* dstDiff, float* srcData, int data_size, float alpha) {
            for (int i = 0; i < data_size; ++i) {
                dstDiff[i] = srcDiff[i] * ((srcData[i] > 0) + (srcData[i] <= 0) * alpha);
            }
        }