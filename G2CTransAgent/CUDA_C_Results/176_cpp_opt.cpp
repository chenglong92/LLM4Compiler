// Optimized code(id = 176): 

void permuteDataTorch(const float* input, float* output, int num, int devideNum, int featureSize, int priorNum, int batchSize) {
    int numPerbatch = num * devideNum * priorNum;
    
    for (int tid = 0; tid < num; ++tid) {
        for (int s = 0; s < batchSize; ++s) {
            for (int i = 0; i < priorNum; ++i) {
                for (int j = 0; j < devideNum; ++j) {
                    output[s * numPerbatch + tid * priorNum * devideNum + i * devideNum + j] = 
                        input[s * numPerbatch + (i * devideNum * featureSize) + (j * featureSize) + tid];
                }
            }
        }
    }
}