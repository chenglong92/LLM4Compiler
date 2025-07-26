// original code(id = 223): 
 /*
__global__ void resetIndices ( long * vec_out , const long N ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx < N ) { vec_out [ idx ] = idx ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void resetIndices(long* vec_out, const long N) {
    for (long idx = 0; idx < N; ++idx) {
        vec_out[idx] = idx;
    }
}

void test_resetIndices() {
    // Test case 1: Normal case
    {
        const long N = 5;
        long vec[N];
        resetIndices(vec, N);
        for (long i = 0; i < N; ++i) {
            assert(vec[i] == i);
        }
    }

    // Test case 2: Empty array
    {
        const long N = 0;
        long vec[1]; // Dummy array
        resetIndices(vec, N);
        // No elements to check
    }

    // Test case 3: Single element
    {
        const long N = 1;
        long vec[N];
        resetIndices(vec, N);
        assert(vec[0] == 0);
    }

    // Test case 4: Large array
    {
        const long N = 100000;
        long* vec = new long[N];
        resetIndices(vec, N);
        for (long i = 0; i < N; ++i) {
            assert(vec[i] == i);
        }
        delete[] vec;
    }

    // Note: Negative N would cause issues but function doesn't check
    // Note: Null pointer would cause issues but function doesn't check
}

int main() {
    test_resetIndices();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}