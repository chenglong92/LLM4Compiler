// Optimized code(id = 129): 

void smallCorrelation(float* L, float* innerSums, int innerSumsLength) {
            for (int u = 0; u < innerSumsLength; ++u) {
                int realIdx = 2 * u;
                int imagIdx = realIdx + 1;
                L[u] = (innerSums[realIdx] * innerSums[realIdx]) + (innerSums[imagIdx] * innerSums[imagIdx]);
            }
        }