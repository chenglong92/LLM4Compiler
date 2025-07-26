// original code(id = 179): 
 /*
__global__ void gpuSearchPosShmem1EQ ( int key , int * devKey , int * devPos , int size ) { int globalTx = blockIdx . x * blockDim . x + threadIdx . x ; if ( globalTx < size ) { if ( devKey [ globalTx ] == key ) { devPos [ 0 ] = globalTx ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void cpuSearchPosShmem1EQ(int key, int* devKey, int* devPos, int size);

int main() {
    // Test case 1: Key found at the beginning
    {
        int devKey[] = {5, 3, 7, 2, 8};
        int devPos = -1;
        cpuSearchPosShmem1EQ(5, devKey, &devPos, 5);
        assert(devPos == 0);
    }

    // Test case 2: Key found in the middle
    {
        int devKey[] = {1, 4, 6, 9, 2};
        int devPos = -1;
        cpuSearchPosShmem1EQ(6, devKey, &devPos, 5);
        assert(devPos == 2);
    }

    // Test case 3: Key found at the end
    {
        int devKey[] = {3, 1, 4, 1, 5};
        int devPos = -1;
        cpuSearchPosShmem1EQ(5, devKey, &devPos, 5);
        assert(devPos == 4);
    }

    // Test case 4: Key not found
    {
        int devKey[] = {2, 4, 6, 8, 10};
        int devPos = -1;
        cpuSearchPosShmem1EQ(5, devKey, &devPos, 5);
        assert(devPos == -1);
    }

    // Test case 5: Empty array
    {
        int devKey[] = {};
        int devPos = -1;
        cpuSearchPosShmem1EQ(5, devKey, &devPos, 0);
        assert(devPos == -1);
    }

    // Test case 6: Multiple occurrences (should return first occurrence)
    {
        int devKey[] = {2, 5, 5, 5, 3};
        int devPos = -1;
        cpuSearchPosShmem1EQ(5, devKey, &devPos, 5);
        assert(devPos == 1);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void cpuSearchPosShmem1EQ(int key, int* devKey, int* devPos, int size) {
    for (int globalTx = 0; globalTx < size; ++globalTx) {
        if (devKey[globalTx] == key) {
            devPos[0] = globalTx;
            return;  // Early exit since we only need the first occurrence
        }
    }
}