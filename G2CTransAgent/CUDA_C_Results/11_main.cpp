// original code(id = 11): 
 /*
__global__ void is_repeat ( int N , int * device_input , int * device_output ) { int idx = blockDim . x * blockIdx . x + threadIdx . x ; if ( idx < N ) { device_output [ idx ] = 0 ; if ( idx + 1 < N && device_input [ idx ] == device_input [ idx + 1 ] ) device_output [ idx ] = 1 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void is_repeat(int N, int* device_input, int* device_output) {
    for (int idx = 0; idx < N; ++idx) {
        device_output[idx] = 0;
        if (idx + 1 < N && device_input[idx] == device_input[idx + 1]) {
            device_output[idx] = 1;
        }
    }
}

void test_is_repeat() {
    // Test case 1: No repeats
    {
        int N = 5;
        int input[] = {1, 2, 3, 4, 5};
        int output[N];
        int expected[] = {0, 0, 0, 0, 0};
        is_repeat(N, input, output);
        for (int i = 0; i < N; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 2: All repeats
    {
        int N = 4;
        int input[] = {2, 2, 2, 2};
        int output[N];
        int expected[] = {1, 1, 1, 0};
        is_repeat(N, input, output);
        for (int i = 0; i < N; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 3: Some repeats
    {
        int N = 6;
        int input[] = {1, 1, 2, 3, 3, 4};
        int output[N];
        int expected[] = {1, 0, 0, 1, 0, 0};
        is_repeat(N, input, output);
        for (int i = 0; i < N; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 4: Single element
    {
        int N = 1;
        int input[] = {5};
        int output[N];
        int expected[] = {0};
        is_repeat(N, input, output);
        for (int i = 0; i < N; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 5: Empty array (should handle gracefully)
    {
        int N = 0;
        int* input = nullptr;
        int* output = nullptr;
        is_repeat(N, input, output); // Should not crash
    }

    // Test case 6: Alternating repeats
    {
        int N = 8;
        int input[] = {1, 1, 2, 2, 3, 3, 4, 4};
        int output[N];
        int expected[] = {1, 1, 1, 1, 1, 1, 1, 0};
        is_repeat(N, input, output);
        for (int i = 0; i < N; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_is_repeat();
    return 0;
}