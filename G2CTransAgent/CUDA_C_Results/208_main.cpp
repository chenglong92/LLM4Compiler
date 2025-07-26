// original code(id = 208): 
 /*
__global__ void vecAdd ( float * in1 , float * in2 , float * out , int len ) { int i = threadIdx . x + blockDim . x * blockIdx . x ; if ( i < len ) out [ i ] = in1 [ i ] + in2 [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void vecAdd(float* in1, float* in2, float* out, int len) {
    for (int i = 0; i < len; ++i) {
        out[i] = in1[i] + in2[i];
    }
}

int main() {
    // Test case 1: Basic addition
    {
        float in1[] = {1.0f, 2.0f, 3.0f};
        float in2[] = {4.0f, 5.0f, 6.0f};
        float out[3];
        float expected[] = {5.0f, 7.0f, 9.0f};
        
        vecAdd(in1, in2, out, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 2: Empty arrays
    {
        float in1[] = {};
        float in2[] = {};
        float out[0];
        
        vecAdd(in1, in2, out, 0);
        // No assertion needed as the function should handle zero-length arrays
    }

    // Test case 3: Negative numbers
    {
        float in1[] = {-1.0f, -2.0f, -3.0f};
        float in2[] = {-4.0f, -5.0f, -6.0f};
        float out[3];
        float expected[] = {-5.0f, -7.0f, -9.0f};
        
        vecAdd(in1, in2, out, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 4: Mixed positive and negative numbers
    {
        float in1[] = {1.0f, -2.0f, 3.0f};
        float in2[] = {-4.0f, 5.0f, -6.0f};
        float out[3];
        float expected[] = {-3.0f, 3.0f, -3.0f};
        
        vecAdd(in1, in2, out, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 5: Large array
    {
        const int len = 1000;
        float in1[len];
        float in2[len];
        float out[len];
        float expected[len];
        
        for (int i = 0; i < len; ++i) {
            in1[i] = static_cast<float>(i);
            in2[i] = static_cast<float>(i * 2);
            expected[i] = in1[i] + in2[i];
        }
        
        vecAdd(in1, in2, out, len);
        
        for (int i = 0; i < len; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 6: Floating point precision
    {
        float in1[] = {0.1f, 0.2f, 0.3f};
        float in2[] = {0.4f, 0.5f, 0.6f};
        float out[3];
        float expected[] = {0.5f, 0.7f, 0.9f};
        
        vecAdd(in1, in2, out, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(out[i] - expected[i] < 1e-6f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}