// original code(id = 197): 
 /*
__global__ void doubleArrayVectorElementwiseMultiplyKernel ( double * d_in_a , double * d_in_b , double * d_out , int length ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in_a [ tid ] * d_in_b [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

void doubleArrayVectorElementwiseMultiply(double* d_in_a, double* d_in_b, double* d_out, int length) {
    for (int i = 0; i < length; ++i) {
        d_out[i] = d_in_a[i] * d_in_b[i];
    }
}

void test_normal_case() {
    const int length = 5;
    double a[length] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double b[length] = {2.0, 3.0, 4.0, 5.0, 6.0};
    double result[length];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);

    for (int i = 0; i < length; ++i) {
        assert(result[i] == a[i] * b[i]);
    }
}

void test_zero_length() {
    const int length = 0;
    double a[1] = {1.0}; // Dummy data
    double b[1] = {2.0}; // Dummy data
    double result[1];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);
    // No operation should be performed, no crash expected
}

void test_negative_numbers() {
    const int length = 3;
    double a[length] = {-1.0, -2.0, -3.0};
    double b[length] = {2.0, -3.0, 4.0};
    double result[length];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);

    for (int i = 0; i < length; ++i) {
        assert(result[i] == a[i] * b[i]);
    }
}

void test_large_numbers() {
    const int length = 2;
    double a[length] = {1.0e300, 2.0e300};
    double b[length] = {2.0, 3.0};
    double result[length];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);

    for (int i = 0; i < length; ++i) {
        assert(result[i] == a[i] * b[i]);
    }
}

void test_small_numbers() {
    const int length = 2;
    double a[length] = {1.0e-300, 2.0e-300};
    double b[length] = {2.0, 3.0};
    double result[length];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);

    for (int i = 0; i < length; ++i) {
        assert(result[i] == a[i] * b[i]);
    }
}

void test_mixed_numbers() {
    const int length = 4;
    double a[length] = {0.0, -0.0, std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN()};
    double b[length] = {1.0, -1.0, 2.0, 3.0};
    double result[length];

    doubleArrayVectorElementwiseMultiply(a, b, result, length);

    assert(result[0] == 0.0);
    assert(result[1] == 0.0);
    assert(result[2] == std::numeric_limits<double>::infinity());
    assert(std::isnan(result[3]));
}

int main() {
    test_normal_case();
    test_zero_length();
    test_negative_numbers();
    test_large_numbers();
    test_small_numbers();
    test_mixed_numbers();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}