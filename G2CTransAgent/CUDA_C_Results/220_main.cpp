// original code(id = 220): 
 /*
__global__ void intSubtract ( int * c , const int * a , const int * b , const unsigned int d ) { int i = threadIdx . x + blockIdx . x * blockDim . x ; if ( i < d ) { c [ i ] = a [ i ] + b [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void intSubtract(int* c, const int* a, const int* b, const unsigned int d) {
    for (unsigned int i = 0; i < d; ++i) {
        c[i] = a[i] + b[i];
    }
}

void test_empty_array() {
    int a[] = {};
    int b[] = {};
    int c[] = {};
    intSubtract(c, a, b, 0);
    std::cout << "Test empty array passed" << std::endl;
}

void test_single_element() {
    int a[] = {5};
    int b[] = {3};
    int c[1];
    intSubtract(c, a, b, 1);
    assert(c[0] == 8);
    std::cout << "Test single element passed" << std::endl;
}

void test_multiple_elements() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50};
    int c[5];
    intSubtract(c, a, b, 5);
    assert(c[0] == 11);
    assert(c[1] == 22);
    assert(c[2] == 33);
    assert(c[3] == 44);
    assert(c[4] == 55);
    std::cout << "Test multiple elements passed" << std::endl;
}

void test_negative_numbers() {
    int a[] = {-1, -2, -3};
    int b[] = {1, 2, 3};
    int c[3];
    intSubtract(c, a, b, 3);
    assert(c[0] == 0);
    assert(c[1] == 0);
    assert(c[2] == 0);
    std::cout << "Test negative numbers passed" << std::endl;
}

void test_mixed_signs() {
    int a[] = {-5, 10, -15, 20};
    int b[] = {5, -10, 15, -20};
    int c[4];
    intSubtract(c, a, b, 4);
    assert(c[0] == 0);
    assert(c[1] == 0);
    assert(c[2] == 0);
    assert(c[3] == 0);
    std::cout << "Test mixed signs passed" << std::endl;
}

void test_zero_values() {
    int a[] = {0, 0, 0};
    int b[] = {0, 0, 0};
    int c[3];
    intSubtract(c, a, b, 3);
    assert(c[0] == 0);
    assert(c[1] == 0);
    assert(c[2] == 0);
    std::cout << "Test zero values passed" << std::endl;
}

void test_large_numbers() {
    int a[] = {INT_MAX, INT_MIN};
    int b[] = {1, -1};
    int c[2];
    intSubtract(c, a, b, 2);
    assert(c[0] == INT_MIN); // Overflow case
    assert(c[1] == INT_MAX); // Underflow case
    std::cout << "Test large numbers passed" << std::endl;
}

int main() {
    test_empty_array();
    test_single_element();
    test_multiple_elements();
    test_negative_numbers();
    test_mixed_signs();
    test_zero_values();
    test_large_numbers();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}