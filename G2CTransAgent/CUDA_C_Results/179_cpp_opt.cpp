// Optimized code(id = 179): 

void cpuSearchPosShmem1EQ(int key, int* devKey, int* devPos, int size) {
    for (int globalTx = 0; globalTx < size; ++globalTx) {
        if (devKey[globalTx] == key) {
            devPos[0] = globalTx;
            return;  // Early exit since we only need the first occurrence
        }
    }
}