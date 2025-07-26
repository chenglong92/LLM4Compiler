// original code(id = 143): 
 /*
__global__ void subAvg ( int * input , int count , int avg ) { int index = blockDim . x * blockIdx . x + threadIdx . x ; if ( index < count ) input [ index ] = input [ index ] - avg ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void subAvg(int* input, int count, int avg) {
    for (int index = 0; index < count; ++index) {
        input[index] = input[index] - avg;
    }
}

void test_subAvg() {
    // Test case 1: Basic test with positive numbers
    {
        int arr[] = {10, 20, 30};
        int count = sizeof(arr) / sizeof(arr[0]);
        int avg = 20;
        subAvg(arr, count, avg);
        assert(arr[0] == -10);
        assert(arr[1] == 0);
        assert(arr[2] == 10);
    }

    // Test case 2: Basic test with negative numbers
    {
        int arr[] = {-10, -20, -30};
        int count = sizeof(arr) / sizeof(arr[0]);
        int avg = -20;
        subAvg(arr, count, avg);
        assert(arr[0] == 10);
        assert(arr[1] == 0);
        assert(arr[2] == -10);
    }

    // Test case 3: Test with mixed positive and negative numbers
    {
        int arr[] = {-5, 0, 5};
        int count = sizeof(arr) / sizeof(arr[0]);
        int avg = 0;
        subAvg(arr, count, avg);
        assert(arr[0] == -5);
        assert(arr[1] == 0);
        assert(arr[2] == 5);
    }

    // Test case 4: Test with single element array
    {
        int arr[] = {100};
        int count = sizeof(arr) / sizeof(arr[0]);
        int avg = 50;
        subAvg(arr, count, avg);
        assert(arr[0] == 50);
    }

    // Test case 5: Test with zero average
    {
        int arr[] = {1, 2, 3, 4, 5};
        int count = sizeof(arr) / sizeof(arr[0]);
        int avg = 0;
        subAvg(arr, count, avg);
        assert(arr[0] == 1);
        assert(arr[1] == 2);
        assert(arr[2] == 3);
        assert(arr[3] == 4);
        assert(arr[4] == 5);
    }

    // Test case 6: Test with empty array (should not crash)
    {
        int* arr = nullptr;
        int count = 0;
        int avg = 10;
        subAvg(arr, count, avg);
        // No assertions, just checking it doesn't crash
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_subAvg();
    return 0;
}