// original code(id = 212): 
 /*
__global__ void set_offset_kernel ( int stride , int size , int * output ) { for ( int i = threadIdx . x ; i < size ; i += blockDim . x ) { output [ i ] = i * stride ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void set_offset(int stride, int size, int* output) {
    for (int i = 0; i < size; ++i) {
        output[i] = i * stride;
    }
}

int main() {
    // Test case 1: Normal case with positive stride and size
    {
        const int stride = 2;
        const int size = 5;
        int output[size];
        set_offset(stride, size, output);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == i * stride);
        }
    }

    // Test case 2: Edge case with size 0
    {
        const int stride = 3;
        const int size = 0;
        int* output = nullptr;
        set_offset(stride, size, output); // Should handle size 0 gracefully
    }

    // Test case 3: Edge case with negative stride (function should still work)
    {
        const int stride = -1;
        const int size = 4;
        int output[size];
        set_offset(stride, size, output);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == i * stride);
        }
    }

    // Test case 4: Large size to test potential overflow
    {
        const int stride = 1;
        const int size = 1000000;
        int* output = new int[size];
        set_offset(stride, size, output);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == i * stride);
        }
        delete[] output;
    }

    // Test case 5: Maximum positive stride
    {
        const int stride = INT_MAX;
        const int size = 3;
        int output[size];
        set_offset(stride, size, output);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == i * stride);
        }
    }

    // Test case 6: Minimum negative stride
    {
        const int stride = INT_MIN;
        const int size = 3;
        int output[size];
        set_offset(stride, size, output);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == i * stride);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}