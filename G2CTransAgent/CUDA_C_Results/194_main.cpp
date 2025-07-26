// original code(id = 194): 
 /*
__global__ void setOffset ( int * offset , int dims , int batchSize ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid > 0 ) { return ; } offset [ 0 ] = 0 ; for ( int i = 1 ; i < batchSize + 1 ; i ++ ) { offset [ i ] = i * dims ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void setOffset(int* offset, int dims, int batchSize) {
    offset[0] = 0;
    for (int i = 1; i < batchSize + 1; ++i) {
        offset[i] = i * dims;
    }
}

void testSetOffset() {
    // Test case 1: batchSize = 0
    {
        int offset[1];
        int dims = 5;
        int batchSize = 0;
        setOffset(offset, dims, batchSize);
        assert(offset[0] == 0);
    }

    // Test case 2: batchSize = 1, dims = 1
    {
        int offset[2];
        int dims = 1;
        int batchSize = 1;
        setOffset(offset, dims, batchSize);
        assert(offset[0] == 0);
        assert(offset[1] == 1);
    }

    // Test case 3: batchSize = 3, dims = 2
    {
        int offset[4];
        int dims = 2;
        int batchSize = 3;
        setOffset(offset, dims, batchSize);
        assert(offset[0] == 0);
        assert(offset[1] == 2);
        assert(offset[2] == 4);
        assert(offset[3] == 6);
    }

    // Test case 4: batchSize = 5, dims = 0
    {
        int offset[6];
        int dims = 0;
        int batchSize = 5;
        setOffset(offset, dims, batchSize);
        assert(offset[0] == 0);
        for (int i = 1; i <= batchSize; ++i) {
            assert(offset[i] == 0);
        }
    }

    // Test case 5: batchSize = 2, dims = -3
    {
        int offset[3];
        int dims = -3;
        int batchSize = 2;
        setOffset(offset, dims, batchSize);
        assert(offset[0] == 0);
        assert(offset[1] == -3);
        assert(offset[2] == -6);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testSetOffset();
    return 0;
}