// original code(id = 32): 
 /*
__global__ void PSIfill ( float * array , int conv_length , int maxThreads ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i >= maxThreads ) return ; array [ i ] = array [ i % conv_length ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void PSIfill(float* array, int conv_length, int maxThreads) {
    for (int i = 0; i < maxThreads; ++i) {
        array[i] = array[i % conv_length];
    }
}

int main() {
    // Test case 1: Normal case with conv_length < maxThreads
    {
        float array1[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        int conv_length1 = 5;
        int maxThreads1 = 10;
        PSIfill(array1, conv_length1, maxThreads1);
        float expected1[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        for (int i = 0; i < maxThreads1; ++i) {
            assert(array1[i] == expected1[i]);
        }
    }

    // Test case 2: conv_length == maxThreads
    {
        float array2[5] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        int conv_length2 = 5;
        int maxThreads2 = 5;
        PSIfill(array2, conv_length2, maxThreads2);
        float expected2[5] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        for (int i = 0; i < maxThreads2; ++i) {
            assert(array2[i] == expected2[i]);
        }
    }

    // Test case 3: conv_length > maxThreads
    {
        float array3[3] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f};
        int conv_length3 = 5;
        int maxThreads3 = 3;
        PSIfill(array3, conv_length3, maxThreads3);
        float expected3[3] = {1.5f, 2.5f, 3.5f};
        for (int i = 0; i < maxThreads3; ++i) {
            assert(array3[i] == expected3[i]);
        }
    }

    // Test case 4: Edge case with maxThreads = 0
    {
        float array4[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        int conv_length4 = 5;
        int maxThreads4 = 0;
        PSIfill(array4, conv_length4, maxThreads4);
        // No operation should be performed
        float expected4[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        for (int i = 0; i < 5; ++i) {
            assert(array4[i] == expected4[i]);
        }
    }

    // Test case 5: Edge case with conv_length = 1
    {
        float array5[5] = {42.0f};
        int conv_length5 = 1;
        int maxThreads5 = 5;
        PSIfill(array5, conv_length5, maxThreads5);
        float expected5[5] = {42.0f, 42.0f, 42.0f, 42.0f, 42.0f};
        for (int i = 0; i < maxThreads5; ++i) {
            assert(array5[i] == expected5[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}