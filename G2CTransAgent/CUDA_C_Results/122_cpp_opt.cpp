// Optimized code(id = 122): 

void invalidateFlow(float* modFlowX, float* modFlowY, const float* constFlowX, const float* constFlowY, int width, int height, float cons_thres) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int ind = y * width + x;
            float mFX = modFlowX[ind];
            float mFY = modFlowY[ind];
            float cFX = constFlowX[ind];
            float cFY = constFlowY[ind];
            float err = (mFX - cFX) * (mFX - cFX) + (mFY - cFY) * (mFY - cFY);
            if (err > cons_thres) {
                mFX = 0;
                mFY = 0;
            }
            modFlowX[ind] = mFX;
            modFlowY[ind] = mFY;
        }
    }
}