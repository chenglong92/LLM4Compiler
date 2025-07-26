// original code(id = 102): 
 /*
__global__ void square ( int * array , int arrayCount ) { int idx = threadIdx . x + blockIdx . x * blockDim . x ; if ( idx < arrayCount ) { array [ idx ] *= array [ idx ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void square(int* array, int arrayCount) {
    for (int idx = 0; idx < arrayCount; ++idx) {
        array[idx] *= array[idx];
    }
}

int main() {
    // Test case 1: Normal case with multiple elements
    {
        int arr1[] = {1, 2, 3, 4, 5};
        int expected1[] = {1, 4, 9, 16, 25};
        square(arr1, 5);
        for (int i = 0; i < 5; ++i) {
            assert(arr1[i] == expected1[i]);
        }
    }

    // Test case 2: Single element array
    {
        int arr2[] = {10};
        int expected2[] = {100};
        square(arr2, 1);
        assert(arr2[0] == expected2[0]);
    }

    // Test case 3: Empty array (should do nothing)
    {
        int* arr3 = nullptr;
        square(arr3, 0);
        // No assertion needed as function should handle this safely
    }

    // Test case 4: Negative numbers
    {
        int arr4[] = {-1, -2, -3};
        int expected4[] = {1, 4, 9};
        square(arr4, 3);
        for (int i = 0; i < 3; ++i) {
            assert(arr4[i] == expected4[i]);
        }
    }

    // Test case 5: Zero value
    {
        int arr5[] = {0};
        int expected5[] = {0};
        square(arr5, 1);
        assert(arr5[0] == expected5[0]);
    }

    // Test case 6: Large numbers
    {
        int arr6[] = {1000, 10000};
        int expected6[] = {1000000, 100000000};
        square(arr6, 2);
        for (int i = 0; i < 2; ++i) {
            assert(arr6[i] == expected6[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}