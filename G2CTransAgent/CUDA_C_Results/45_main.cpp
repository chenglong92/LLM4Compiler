// original code(id = 45): 
 /*
__global__ void set_sorting_offset ( const int nrows , const int ncols , int * offsets ) { int tid = threadIdx . x + blockIdx . x * blockDim . x ; if ( tid <= ncols ) offsets [ tid ] = tid * nrows ; return ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void set_sorting_offset(const int nrows, const int ncols, int* offsets) {
    for (int tid = 0; tid <= ncols; ++tid) {
        offsets[tid] = tid * nrows;
    }
}

void test_set_sorting_offset() {
    // Test case 1: Basic case with nrows=3, ncols=4
    {
        int nrows = 3;
        int ncols = 4;
        int offsets[5]; // ncols + 1 elements
        set_sorting_offset(nrows, ncols, offsets);
        assert(offsets[0] == 0);
        assert(offsets[1] == 3);
        assert(offsets[2] == 6);
        assert(offsets[3] == 9);
        assert(offsets[4] == 12);
    }

    // Test case 2: Single row and column
    {
        int nrows = 1;
        int ncols = 1;
        int offsets[2];
        set_sorting_offset(nrows, ncols, offsets);
        assert(offsets[0] == 0);
        assert(offsets[1] == 1);
    }

    // Test case 3: Zero columns (edge case)
    {
        int nrows = 5;
        int ncols = 0;
        int offsets[1];
        set_sorting_offset(nrows, ncols, offsets);
        assert(offsets[0] == 0);
    }

    // Test case 4: Large values
    {
        int nrows = 1000;
        int ncols = 1000;
        int* offsets = new int[ncols + 1];
        set_sorting_offset(nrows, ncols, offsets);
        assert(offsets[0] == 0);
        assert(offsets[500] == 500000);
        assert(offsets[1000] == 1000000);
        delete[] offsets;
    }

    // Test case 5: Negative nrows or ncols (should handle but behavior undefined per function design)
    // Note: This test case is included but may not be meaningful as the function doesn't validate inputs
    {
        int nrows = -2;
        int ncols = 3;
        int offsets[4];
        set_sorting_offset(nrows, ncols, offsets);
        // The behavior is technically undefined for negative inputs
        // We're just checking it runs without crashing
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_set_sorting_offset();
    return 0;
}