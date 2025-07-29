// original code(id = 11): 
 /*
__global__ void is_repeat ( int N , int * device_input , int * device_output ) { int idx = blockDim . x * blockIdx . x + threadIdx . x ; if ( idx < N ) { device_output [ idx ] = 0 ; if ( idx + 1 < N && device_input [ idx ] == device_input [ idx + 1 ] ) device_output [ idx ] = 1 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void is_repeat(int N, int* device_input, int* device_output);

void test_is_repeat() {
    // Test case 1: Empty array
    {
        int* input = nullptr;
        int* output = nullptr;
        is_repeat(0, input, output);
        // No output to check, just verify it doesn't crash
        std::cout << "Test case 1 passed (empty array)" << std::endl;
    }

    // Test case 2: Single element array
    {
        int input[] = {5};
        int output[1];
        is_repeat(1, input, output);
        assert(output[0] == 0);
        std::cout << "Test case 2 passed (single element)" << std::endl;
    }

    // Test case 3: No repeating elements
    {
        int input[] = {1, 2, 3, 4, 5};
        int output[5];
        is_repeat(5, input, output);
        for (int i = 0; i < 5; ++i) {
            assert(output[i] == 0);
        }
        std::cout << "Test case 3 passed (no repeats)" << std::endl;
    }

    // Test case 4: Some repeating elements
    {
        int input[] = {1, 1, 2, 3, 3, 3, 4, 5};
        int expected[] = {1, 0, 0, 1, 1, 0, 0, 0};
        int output[8];
        is_repeat(8, input, output);
        for (int i = 0; i < 8; ++i) {
            assert(output[i] == expected[i]);
        }
        std::cout << "Test case 4 passed (some repeats)" << std::endl;
    }

    // Test case 5: All repeating elements
    {
        int input[] = {7, 7, 7, 7, 7};
        int expected[] = {1, 1, 1, 1, 0};
        int output[5];
        is_repeat(5, input, output);
        for (int i = 0; i < 5; ++i) {
            assert(output[i] == expected[i]);
        }
        std::cout << "Test case 5 passed (all repeats)" << std::endl;
    }

    // Test case 6: Repeating elements at the end
    {
        int input[] = {1, 2, 3, 4, 5, 5};
        int expected[] = {0, 0, 0, 0, 1, 0};
        int output[6];
        is_repeat(6, input, output);
        for (int i = 0; i < 6; ++i) {
            assert(output[i] == expected[i]);
        }
        std::cout << "Test case 6 passed (repeats at end)" << std::endl;
    }
}

int main() {
    test_is_repeat();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void is_repeat(int N, int* device_input, int* device_output) {
    for (int idx = 0; idx < N; ++idx) {
        device_output[idx] = 0;
        if (idx + 1 < N && device_input[idx] == device_input[idx + 1]) {
            device_output[idx] = 1;
        }
    }
}