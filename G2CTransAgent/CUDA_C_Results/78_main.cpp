// original code(id = 78): 
 /*
__global__ void compute_array_square ( float * array , float * outArray , int size ) { int thread_index = threadIdx . x + blockIdx . x * blockDim . x ; int num_threads = blockDim . x * gridDim . x ; for ( int i = 0 ; i < size ; i += num_threads ) { int index = i + thread_index ; if ( index < size ) { outArray [ index ] = array [ index ] * array [ index ] ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void compute_array_square(float* array, float* outArray, int size) {
    for (int index = 0; index < size; ++index) {
        outArray[index] = array[index] * array[index];
    }
}

int main() {
    // Test case 1: Basic test with positive numbers
    {
        float input[] = {1.0f, 2.0f, 3.0f, 4.0f};
        float output[4];
        compute_array_square(input, output, 4);
        assert(output[0] == 1.0f);
        assert(output[1] == 4.0f);
        assert(output[2] == 9.0f);
        assert(output[3] == 16.0f);
    }

    // Test case 2: Test with negative numbers
    {
        float input[] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float output[4];
        compute_array_square(input, output, 4);
        assert(output[0] == 1.0f);
        assert(output[1] == 4.0f);
        assert(output[2] == 9.0f);
        assert(output[3] == 16.0f);
    }

    // Test case 3: Test with zero
    {
        float input[] = {0.0f};
        float output[1];
        compute_array_square(input, output, 1);
        assert(output[0] == 0.0f);
    }

    // Test case 4: Test with mixed positive, negative, and zero values
    {
        float input[] = {-1.5f, 0.0f, 2.5f, -3.5f};
        float output[4];
        compute_array_square(input, output, 4);
        assert(output[0] == 2.25f);
        assert(output[1] == 0.0f);
        assert(output[2] == 6.25f);
        assert(output[3] == 12.25f);
    }

    // Test case 5: Test with large array
    {
        const int size = 1000;
        float input[size];
        float output[size];
        for (int i = 0; i < size; ++i) {
            input[i] = static_cast<float>(i);
        }
        compute_array_square(input, output, size);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == static_cast<float>(i * i));
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}