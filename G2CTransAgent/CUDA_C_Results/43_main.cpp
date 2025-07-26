// original code(id = 43): 
 /*
__global__ void gpu_add ( float * c , float * a , float * b , int n ) { int j = blockIdx . x * blockDim . x + threadIdx . x ; c [ j ] = a [ j ] + b [ j ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <limits>

void cpu_add(float* c, float* a, float* b, int n) {
    for (int j = 0; j < n; ++j) {
        c[j] = a[j] + b[j];
    }
}

int main() {
    // Test case 1: Basic addition
    {
        float a[] = {1.0f, 2.0f, 3.0f};
        float b[] = {4.0f, 5.0f, 6.0f};
        float c[3];
        float expected[] = {5.0f, 7.0f, 9.0f};
        cpu_add(c, a, b, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Addition with zero
    {
        float a[] = {0.0f, 0.0f, 0.0f};
        float b[] = {1.0f, 2.0f, 3.0f};
        float c[3];
        float expected[] = {1.0f, 2.0f, 3.0f};
        cpu_add(c, a, b, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 3: Negative numbers
    {
        float a[] = {-1.0f, -2.0f, -3.0f};
        float b[] = {4.0f, 5.0f, 6.0f};
        float c[3];
        float expected[] = {3.0f, 3.0f, 3.0f};
        cpu_add(c, a, b, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Large numbers
    {
        float a[] = {1e20f, 2e20f, 3e20f};
        float b[] = {4e20f, 5e20f, 6e20f};
        float c[3];
        float expected[] = {5e20f, 7e20f, 9e20f};
        cpu_add(c, a, b, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: Single element
    {
        float a[] = {42.0f};
        float b[] = {58.0f};
        float c[1];
        float expected[] = {100.0f};
        cpu_add(c, a, b, 1);
        assert(c[0] == expected[0]);
    }

    // Test case 6: Empty arrays (should do nothing)
    {
        float a[] = {};
        float b[] = {};
        float c[] = {};
        cpu_add(c, a, b, 0);
        // No assertion needed as it should just not crash
    }

    // Test case 7: Maximum float values
    {
        float max_val = std::numeric_limits<float>::max();
        float a[] = {max_val, max_val, max_val};
        float b[] = {max_val, max_val, max_val};
        float c[3];
        float expected[] = {max_val * 2, max_val * 2, max_val * 2};
        cpu_add(c, a, b, 3);
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 8: Infinity
    {
        float inf = std::numeric_limits<float>::infinity();
        float a[] = {inf, 1.0f, inf};
        float b[] = {inf, inf, -inf};
        float c[3];
        float expected[] = {inf, inf, std::numeric_limits<float>::quiet_NaN()};
        cpu_add(c, a, b, 3);
        assert(c[0] == expected[0]);
        assert(c[1] == expected[1]);
        assert(std::isnan(c[2]));
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}