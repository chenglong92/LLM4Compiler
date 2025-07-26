// original code(id = 142): 
 /*
__global__ void test1 ( float * input , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( input [ tid * 4 ] != 0 ) { input [ tid * 4 ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void test1(float* input, int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (input[tid * 4] != 0) {
            input[tid * 4] = 0;
        }
    }
}

void printArray(float* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void test_case1() {
    float input[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
    int dims = 2;
    test1(input, dims);
    assert(input[0] == 0.0f);
    assert(input[4] == 0.0f);
    assert(input[1] == 2.0f);  // Should remain unchanged
    assert(input[7] == 8.0f);  // Should remain unchanged
    std::cout << "Test Case 1 Passed!" << std::endl;
}

void test_case2() {
    float input[] = {0.0f, 1.0f, 2.0f, 3.0f, 0.0f, 4.0f, 5.0f, 6.0f};
    int dims = 2;
    test1(input, dims);
    assert(input[0] == 0.0f);
    assert(input[4] == 0.0f);
    assert(input[1] == 1.0f);  // Should remain unchanged
    assert(input[7] == 6.0f);  // Should remain unchanged
    std::cout << "Test Case 2 Passed!" << std::endl;
}

void test_case3() {
    float input[] = {0.0f};
    int dims = 0;
    test1(input, dims);
    // No assertions as function shouldn't modify anything
    std::cout << "Test Case 3 Passed!" << std::endl;
}

void test_case4() {
    float input[] = {1.5f};
    int dims = 1;
    test1(input, dims);
    assert(input[0] == 0.0f);
    std::cout << "Test Case 4 Passed!" << std::endl;
}

void test_case5() {
    float input[] = {1.1f, 2.2f, 3.3f, 4.4f, 0.0f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 0.0f, 10.0f};
    int dims = 3;
    test1(input, dims);
    assert(input[0] == 0.0f);
    assert(input[4] == 0.0f);
    assert(input[8] == 0.0f);
    assert(input[1] == 2.2f);   // Should remain unchanged
    assert(input[11] == 10.0f); // Should remain unchanged
    std::cout << "Test Case 5 Passed!" << std::endl;
}

int main() {
    test_case1();
    test_case2();
    test_case3();
    test_case4();
    test_case5();
    return 0;
}