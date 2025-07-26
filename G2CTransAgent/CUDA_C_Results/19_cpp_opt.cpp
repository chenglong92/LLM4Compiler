// Optimized code(id = 19): 

#include <vector>

void getTopkNum(const float* inputScore, const int* inputIndex, float* outputScore, int* outputIndex, 
                float threshold, const int dims, int* anchorIndex, int* classIndex, 
                const int classNum, int batchSize, int totalScoreNum) {
    
    for (int tid = 0; tid < dims; ++tid) {
        for (int i = 0; i < batchSize; ++i) {
            if (inputScore[i * totalScoreNum + tid] >= threshold) {
                outputScore[i * dims + tid] = inputScore[i * totalScoreNum + tid];
                outputIndex[i * dims + tid] = inputIndex[i * totalScoreNum + tid];
                anchorIndex[i * dims + tid] = outputIndex[i * dims + tid] / classNum;
                classIndex[i * dims + tid] = outputIndex[i * dims + tid] % classNum;
            } else {
                outputScore[i * dims + tid] = 0.0f;
                outputIndex[i * dims + tid] = -1;
                anchorIndex[i * dims + tid] = -1;
                classIndex[i * dims + tid] = -1;
            }
        }
    }
}