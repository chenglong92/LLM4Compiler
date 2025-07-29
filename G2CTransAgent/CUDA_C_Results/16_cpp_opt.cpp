// Optimized code(id = 16): 

void estimateSnr(const float* corrSum, const int* corrValidCount, const float* maxval, float* snrValue, int size) {
            for (int idx = 0; idx < size; ++idx) {
                float mean = (corrSum[idx] - maxval[idx] * maxval[idx]) / (corrValidCount[idx] - 1);
                snrValue[idx] = maxval[idx] * maxval[idx] / mean;
            }
        }