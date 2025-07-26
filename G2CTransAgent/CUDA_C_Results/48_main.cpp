// original code(id = 48): 
 /*
__global__ void VectorAdd ( float * arrayA , float * arrayB , float * output ) { int idx = threadIdx . x ; output [ idx ] = arrayA [ idx ] + arrayB [ idx ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void VectorAdd(float* arrayA, float* arrayB, float* output, int size) {
    for (int idx = 0; idx < size; ++idx) {
        output[idx] = arrayA[idx] + arrayB[idx];
    }
}

void test_VectorAdd() {
    // Test case 1: Normal case with positive numbers
    {
        float arrayA[] = {1.0f, 2.0f, 3.0f};
        float arrayB[] = {4.0f, 5.0f, 6.0f};
        float output[3];
        float expected[] = {5.0f, 7.0f, 9.0f};
        VectorAdd(arrayA, arrayB, output, 3);
        for (int i = 0; i < 3; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 2: Normal case with negative numbers
    {
        float arrayA[] = {-1.0f, -2.0f, -3.0f};
        float arrayB[] = {-4.0f, -5.0f, -6.0f};
        float output[3];
        float expected[] = {-5.0f, -7.0f, -9.0f};
        VectorAdd(arrayA, arrayB, output, 3);
        for (int i = 0; i < 3; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 3: Mixed positive and negative numbers
    {
        float arrayA[] = {1.0f, -2.0f, 3.0f};
        float arrayB[] = {-4.0f, 5.0f, -6.0f};
        float output[3];
        float expected[] = {-3.0f, 3.0f, -3.0f};
        VectorAdd(arrayA, arrayB, output, 3);
        for (int i = 0; i < 3; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 4: Single element arrays
    {
        float arrayA[] = {42.0f};
        float arrayB[] = {58.0f};
        float output[1];
        float expected[] = {100.0f};
        VectorAdd(arrayA, arrayB, output, 1);
        assert(output[0] == expected[0]);
    }

    // Test case 5: Zero elements (edge case)
    {
        float arrayA[] = {};
        float arrayB[] = {};
        float output[0];
        VectorAdd(arrayA, arrayB, output, 0);
        // No assertion needed as the function should handle size=0 without issues
    }

    // Test case 6: Large arrays
    {
        const int size = 1000;
        float arrayA[size];
        float arrayB[size];
        float output[size];
        float expected[size];
        for (int i = 0; i < size; ++i) {
            arrayA[i] = static_cast<float>(i);
            arrayB[i] = static_cast<float>(i * 2);
            expected[i] = arrayA[i] + arrayB[i];
        }
        VectorAdd(arrayA, arrayB, output, size);
        for (int i = 0; i < size; ++i) {
            assert(output[i] == expected[i]);
        }
    }

    // Test case 7: Floating point precision
    {
        float arrayA[] = {0.1f, 0.2f, 0.3f};
        float arrayB[] = {0.4f, 0.5f, 0.6f};
        float output[3];
        float expected[] = {0.5f, 0.7f, 0.9f};
        VectorAdd(arrayA, arrayB, output, 3);
        for (int i = 0; i < 3; ++i) {
            assert(output[i] - expected[i] < 1e-6f);
        }
    }
}

int main() {
    test_VectorAdd();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}