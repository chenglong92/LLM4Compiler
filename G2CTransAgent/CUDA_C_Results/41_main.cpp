// original code(id = 41): 
 /*
__global__ void memsetCudaInt ( int * data , int val , int N ) { unsigned int index = blockDim . x * blockIdx . x + threadIdx . x ; if ( index >= N ) { return ; } data [ index ] = val ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void memsetCudaInt(int* data, int val, int N) {
    for (unsigned int index = 0; index < N; ++index) {
        data[index] = val;
    }
}

int main() {
    // Test case 1: Normal case with positive N
    {
        const int N = 5;
        int data[N];
        int val = 10;
        memsetCudaInt(data, val, N);
        for (int i = 0; i < N; ++i) {
            assert(data[i] == val);
        }
    }

    // Test case 2: Boundary case with N = 0
    {
        const int N = 0;
        int* data = nullptr;
        int val = 10;
        memsetCudaInt(data, val, N);
        // No operation expected, just ensure no crash
    }

    // Test case 3: Boundary case with large N
    {
        const int N = 1000000;
        int* data = new int[N];
        int val = -1;
        memsetCudaInt(data, val, N);
        for (int i = 0; i < N; ++i) {
            assert(data[i] == val);
        }
        delete[] data;
    }

    // Test case 4: Error case with negative N (should be handled by unsigned int)
    {
        const int N = -5;
        int* data = new int[5]; // Allocate some memory to avoid nullptr
        int val = 10;
        memsetCudaInt(data, val, N); // N is converted to a large unsigned value
        // Behavior is undefined, but test ensures it compiles and runs
        delete[] data;
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}