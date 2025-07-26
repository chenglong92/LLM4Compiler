// Optimized code(id = 201): 

void sumAndScale(float* noiseVariance, float* diffMag2, int n) {
    for (int i = 0; i < n; ++i) {
        int batchJump = i * 347;
        float temp = 0.0f;
        for (int sumIndex = 0; sumIndex < 347; ++sumIndex) {
            temp += diffMag2[batchJump + sumIndex];
        }
        noiseVariance[i] = 0.00161812f * temp;
    }
}