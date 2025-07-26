// Optimized code(id = 39): 

void LreluForward(float* srcData, float* dstData, int data_size, float alpha) {
    for (int index = 0; index < data_size; ++index) {
        dstData[index] = srcData[index] > 0 ? srcData[index] : srcData[index] * alpha;
    }
}