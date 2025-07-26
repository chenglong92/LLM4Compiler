// original code(id = 217): 
 /*
__global__ void binarize_kernel ( float * x , int n , float * binary ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i >= n ) return ; binary [ i ] = ( x [ i ] >= 0 ) ? 1 : -1 ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void binarize_kernel(float* x, int n, float* binary) {
    for (int i = 0; i < n; ++i) {
        binary[i] = (x[i] >= 0) ? 1.0f : -1.0f;
    }
}

int main() {
    // Test case 1: All positive values
    {
        float input[] = {1.0f, 2.5f, 3.7f, 0.1f};
        float output[4];
        float expected[] = {1.0f, 1.0f, 1.0f, 1.0f};
        binarize_kernel(input, 4, output);
        for (int i = 0; i < 4; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 2: All negative values
    {
        float input[] = {-1.0f, -2.5f, -3.7f, -0.1f};
        float output[4];
        float expected[] = {-1.0f, -1.0f, -1.0f, -1.0f};
        binarize_kernel(input, 4, output);
        for (int i = 0; i < 4; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 3: Mixed positive and negative values
    {
        float input[] = {-1.0f, 2.5f, -3.7f, 0.0f, 4.2f};
        float output[5];
        float expected[] = {-1.0f, 1.0f, -1.0f, 1.0f, 1.0f};
        binarize_kernel(input, 5, output);
        for (int i = 0; i < 5; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 4: Single element (positive)
    {
        float input[] = {0.0f};
        float output[1];
        float expected[] = {1.0f};
        binarize_kernel(input, 1, output);
        assert(output[0] == expected[0]);
    }

    // Test case 5: Single element (negative)
    {
        float input[] = {-0.0f};  // This will still be treated as 0.0f
        float output[1];
        float expected[] = {1.0f};
        binarize_kernel(input, 1, output);
        assert(output[0] == expected[0]);
    }

    // Test case 6: Empty array
    {
        float* input = nullptr;
        float* output = nullptr;
        binarize_kernel(input, 0, output);  // Should not crash
    }

    // Test case 7: Exactly zero values
    {
        float input[] = {0.0f, -0.0f, 0.0f};
        float output[3];
        float expected[] = {1.0f, 1.0f, 1.0f};
        binarize_kernel(input, 3, output);
        for (int i = 0; i < 3; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}