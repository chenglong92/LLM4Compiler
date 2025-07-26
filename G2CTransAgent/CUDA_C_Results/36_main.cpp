// original code(id = 36): 
 /*
__global__ void doubleArrayVectorAddKernel ( double * d_in_a , double * d_in_b , double * d_out , int length ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in_a [ tid ] + d_in_b [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void doubleArrayVectorAdd(double* d_in_a, double* d_in_b, double* d_out, int length) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in_a[tid] + d_in_b[tid];
    }
}

void test_empty_arrays() {
    double a[1], b[1], out[1];
    doubleArrayVectorAdd(a, b, out, 0);
    std::cout << "Test empty arrays: passed" << std::endl;
}

void test_single_element() {
    double a[] = {1.5};
    double b[] = {2.5};
    double out[1];
    doubleArrayVectorAdd(a, b, out, 1);
    assert(out[0] == 4.0);
    std::cout << "Test single element: passed" << std::endl;
}

void test_multiple_elements() {
    double a[] = {1.0, 2.0, 3.0};
    double b[] = {4.0, 5.0, 6.0};
    double out[3];
    doubleArrayVectorAdd(a, b, out, 3);
    assert(out[0] == 5.0);
    assert(out[1] == 7.0);
    assert(out[2] == 9.0);
    std::cout << "Test multiple elements: passed" << std::endl;
}

void test_negative_values() {
    double a[] = {-1.0, -2.0, -3.0};
    double b[] = {1.0, 2.0, 3.0};
    double out[3];
    doubleArrayVectorAdd(a, b, out, 3);
    assert(out[0] == 0.0);
    assert(out[1] == 0.0);
    assert(out[2] == 0.0);
    std::cout << "Test negative values: passed" << std::endl;
}

void test_mixed_values() {
    double a[] = {1.5, -2.5, 0.0};
    double b[] = {-1.5, 2.5, 0.0};
    double out[3];
    doubleArrayVectorAdd(a, b, out, 3);
    assert(out[0] == 0.0);
    assert(out[1] == 0.0);
    assert(out[2] == 0.0);
    std::cout << "Test mixed values: passed" << std::endl;
}

void test_large_arrays() {
    const int size = 1000;
    double a[size], b[size], out[size];
    for (int i = 0; i < size; ++i) {
        a[i] = i * 1.1;
        b[i] = i * 2.2;
    }
    doubleArrayVectorAdd(a, b, out, size);
    for (int i = 0; i < size; ++i) {
        assert(fabs(out[i] - (a[i] + b[i])) < 1e-9);
    }
    std::cout << "Test large arrays: passed" << std::endl;
}

void test_extreme_values() {
    double a[] = {DBL_MAX, DBL_MIN, -DBL_MAX};
    double b[] = {DBL_MAX, DBL_MIN, DBL_MAX};
    double out[3];
    doubleArrayVectorAdd(a, b, out, 3);
    assert(out[0] == DBL_MAX * 2);
    assert(out[1] == DBL_MIN * 2);
    assert(out[2] == 0.0);
    std::cout << "Test extreme values: passed" << std::endl;
}

int main() {
    test_empty_arrays();
    test_single_element();
    test_multiple_elements();
    test_negative_values();
    test_mixed_values();
    test_large_arrays();
    test_extreme_values();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}