// original code(id = 199): 
 /*
__global__ void fill_idx ( int N , int * device_input , int * device_output ) { int idx = blockDim . x * blockIdx . x + threadIdx . x ; if ( idx + 1 < N && device_input [ idx ] + 1 == device_input [ idx + 1 ] ) { device_output [ device_input [ idx ] ] = idx ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void fill_idx(int N, int* device_input, int* device_output) {
    for (int idx = 0; idx < N - 1; ++idx) {
        if (device_input[idx] + 1 == device_input[idx + 1]) {
            device_output[device_input[idx]] = idx;
        }
    }
}

void test_fill_idx() {
    // Test case 1: Normal case with consecutive elements
    {
        int N = 5;
        int device_input[] = {1, 2, 3, 4, 5};
        int device_output[6] = {-1}; // Initialize with -1
        fill_idx(N, device_input, device_output);
        assert(device_output[1] == 0);
        assert(device_output[2] == 1);
        assert(device_output[3] == 2);
        assert(device_output[4] == 3);
        assert(device_output[5] == -1); // Not set
    }

    // Test case 2: No consecutive elements
    {
        int N = 4;
        int device_input[] = {1, 3, 5, 7};
        int device_output[8] = {-1};
        fill_idx(N, device_input, device_output);
        for (int i = 0; i < 8; ++i) {
            assert(device_output[i] == -1);
        }
    }

    // Test case 3: Mixed consecutive and non-consecutive elements
    {
        int N = 6;
        int device_input[] = {1, 2, 4, 5, 7, 8};
        int device_output[9] = {-1};
        fill_idx(N, device_input, device_output);
        assert(device_output[1] == 0);
        assert(device_output[2] == 1);
        assert(device_output[4] == 2);
        assert(device_output[5] == 3);
        assert(device_output[7] == 4);
        assert(device_output[8] == 5);
        assert(device_output[0] == -1);
        assert(device_output[3] == -1);
        assert(device_output[6] == -1);
    }

    // Test case 4: Single element (edge case)
    {
        int N = 1;
        int device_input[] = {1};
        int device_output[2] = {-1};
        fill_idx(N, device_input, device_output);
        assert(device_output[1] == -1);
    }

    // Test case 5: Empty array (edge case)
    {
        int N = 0;
        int* device_input = nullptr;
        int device_output[1] = {-1};
        fill_idx(N, device_input, device_output);
        // No assertions, just checking it doesn't crash
    }

    // Test case 6: Large consecutive sequence
    {
        const int N = 1000;
        int device_input[N];
        int device_output[N + 1];
        for (int i = 0; i < N; ++i) {
            device_input[i] = i + 1;
            device_output[i + 1] = -1;
        }
        fill_idx(N, device_input, device_output);
        for (int i = 1; i < N; ++i) {
            assert(device_output[i] == i - 1);
        }
        assert(device_output[N] == -1);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_fill_idx();
    return 0;
}