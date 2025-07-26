// original code(id = 141): 
 /*
__global__ void clearArray ( unsigned char * arr , const unsigned int lenght ) { unsigned int offset = blockDim . x * blockIdx . x + threadIdx . x ; unsigned int skip = gridDim . x * blockDim . x ; while ( offset < lenght ) { arr [ offset ] = 0 ; offset += skip ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void clearArray(unsigned char* arr, const unsigned int length) {
            for (unsigned int i = 0; i < length; ++i) {
                arr[i] = 0;
            }
        }

        int main() {
            // Test case 1: Clear a non-empty array
            unsigned char arr1[5] = {1, 2, 3, 4, 5};
            clearArray(arr1, 5);
            for (unsigned int i = 0; i < 5; ++i) {
                assert(arr1[i] == 0);
            }

            // Test case 2: Clear an empty array (length 0)
            unsigned char arr2[0];
            clearArray(arr2, 0);
            // No elements to check, but should not crash

            // Test case 3: Clear a large array
            const unsigned int largeSize = 1000;
            unsigned char arr3[largeSize];
            for (unsigned int i = 0; i < largeSize; ++i) {
                arr3[i] = i % 256;
            }
            clearArray(arr3, largeSize);
            for (unsigned int i = 0; i < largeSize; ++i) {
                assert(arr3[i] == 0);
            }

            // Test case 4: Clear part of an array
            unsigned char arr4[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            clearArray(arr4, 5); // Clear first 5 elements
            for (unsigned int i = 0; i < 5; ++i) {
                assert(arr4[i] == 0);
            }
            for (unsigned int i = 5; i < 10; ++i) {
                assert(arr4[i] == i + 1); // Check remaining elements unchanged
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }