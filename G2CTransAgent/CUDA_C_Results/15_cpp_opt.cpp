// Optimized code(id = 15): 

void cpuMatrMultD(float* Ad, float* Bd, float* Cd, int rowsA, int colsA, int colsB) {
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            Cd[i * colsB + j] = 0;
            for (int k = 0; k < colsA; ++k) {
                Cd[i * colsB + j] += Ad[i * colsA + k] * Bd[k * colsB + j];
            }
        }
    }
}