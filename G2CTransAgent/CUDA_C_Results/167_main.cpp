// original code(id = 167): 
 /*
__global__ void flipKernel ( float * array1 , int width ) { int current_index = blockIdx . x * blockDim . x + threadIdx . x ; int replace = ( width - 1 - current_index / width ) * width + current_index % width ; if ( current_index < width * width / 2 ) { float temp = array1 [ current_index ] ; array1 [ current_index ] = array1 [ replace ] ; array1 [ replace ] = temp ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void flipKernel(float* array1, int width) {
    for (int current_index = 0; current_index < width * width / 2; ++current_index) {
        int replace = (width - 1 - current_index / width) * width + current_index % width;
        float temp = array1[current_index];
        array1[current_index] = array1[replace];
        array1[replace] = temp;
    }
}

void testFlipKernel() {
    // Test case 1: 1x1 kernel (no change expected)
    {
        float kernel1[] = {1.0f};
        flipKernel(kernel1, 1);
        assert(kernel1[0] == 1.0f);
    }

    // Test case 2: 2x2 kernel
    {
        float kernel2[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float expected2[] = {4.0f, 3.0f, 2.0f, 1.0f};
        flipKernel(kernel2, 2);
        for (int i = 0; i < 4; ++i) {
            assert(kernel2[i] == expected2[i]);
        }
    }

    // Test case 3: 3x3 kernel
    {
        float kernel3[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        float expected3[] = {9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        flipKernel(kernel3, 3);
        for (int i = 0; i < 9; ++i) {
            assert(kernel3[i] == expected3[i]);
        }
    }

    // Test case 4: 4x4 kernel
    {
        float kernel4[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                           9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
        float expected4[] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f,
                            8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        flipKernel(kernel4, 4);
        for (int i = 0; i < 16; ++i) {
            assert(kernel4[i] == expected4[i]);
        }
    }

    // Test case 5: 5x5 kernel (odd dimension)
    {
        float kernel5[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                           6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                           11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                           16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                           21.0f, 22.0f, 23.0f, 24.0f, 25.0f};
        float expected5[] = {25.0f, 24.0f, 23.0f, 22.0f, 21.0f,
                            20.0f, 19.0f, 18.0f, 17.0f, 16.0f,
                            15.0f, 14.0f, 13.0f, 12.0f, 11.0f,
                            10.0f, 9.0f, 8.0f, 7.0f, 6.0f,
                            5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
        flipKernel(kernel5, 5);
        for (int i = 0; i < 25; ++i) {
            assert(kernel5[i] == expected5[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testFlipKernel();
    return 0;
}