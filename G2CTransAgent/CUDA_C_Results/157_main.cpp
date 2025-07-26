// original code(id = 157): 
 /*
__global__ void Mul_half ( float * src , float * dst ) { int index = threadIdx . x ; if ( index < 3 ) { dst [ index ] = src [ index ] * 0.5 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void Mul_half(float* src, float* dst) {
    for (int index = 0; index < 3; ++index) {
        dst[index] = src[index] * 0.5f;
    }
}

int main() {
    // Test case 1: Basic test with positive values
    float src1[3] = {2.0f, 4.0f, 6.0f};
    float dst1[3] = {0.0f, 0.0f, 0.0f};
    float expected1[3] = {1.0f, 2.0f, 3.0f};
    Mul_half(src1, dst1);
    for (int i = 0; i < 3; ++i) {
        assert(dst1[i] == expected1[i]);
    }

    // Test case 2: Test with negative values
    float src2[3] = {-2.0f, -4.0f, -6.0f};
    float dst2[3] = {0.0f, 0.0f, 0.0f};
    float expected2[3] = {-1.0f, -2.0f, -3.0f};
    Mul_half(src2, dst2);
    for (int i = 0; i < 3; ++i) {
        assert(dst2[i] == expected2[i]);
    }

    // Test case 3: Test with zero values
    float src3[3] = {0.0f, 0.0f, 0.0f};
    float dst3[3] = {0.0f, 0.0f, 0.0f};
    float expected3[3] = {0.0f, 0.0f, 0.0f};
    Mul_half(src3, dst3);
    for (int i = 0; i < 3; ++i) {
        assert(dst3[i] == expected3[i]);
    }

    // Test case 4: Test with mixed positive and negative values
    float src4[3] = {1.5f, -3.0f, 0.0f};
    float dst4[3] = {0.0f, 0.0f, 0.0f};
    float expected4[3] = {0.75f, -1.5f, 0.0f};
    Mul_half(src4, dst4);
    for (int i = 0; i < 3; ++i) {
        assert(dst4[i] == expected4[i]);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}