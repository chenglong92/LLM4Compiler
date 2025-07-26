// original code(id = 180): 
 /*
__global__ void doubleArrayVectorSubtractKernel ( double * d_in_a , double * d_in_b , double * d_out , int length ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in_a [ tid ] - d_in_b [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void doubleArrayVectorSubtract(double* d_in_a, double* d_in_b, double* d_out, int length);

int main() {
    // Test case 1: Simple subtraction with positive numbers
    {
        double a[] = {5.0, 3.0, 10.0};
        double b[] = {2.0, 1.0, 4.0};
        double result[3];
        double expected[] = {3.0, 2.0, 6.0};
        
        doubleArrayVectorSubtract(a, b, result, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 2: Subtraction with negative numbers
    {
        double a[] = {-5.0, -3.0, -10.0};
        double b[] = {-2.0, -1.0, -4.0};
        double result[3];
        double expected[] = {-3.0, -2.0, -6.0};
        
        doubleArrayVectorSubtract(a, b, result, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 3: Mixed positive and negative numbers
    {
        double a[] = {5.0, -3.0, 0.0};
        double b[] = {-2.0, 1.0, 4.0};
        double result[3];
        double expected[] = {7.0, -4.0, -4.0};
        
        doubleArrayVectorSubtract(a, b, result, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 4: Single element arrays
    {
        double a[] = {8.5};
        double b[] = {3.2};
        double result[1];
        double expected[] = {5.3};
        
        doubleArrayVectorSubtract(a, b, result, 1);
        
        assert(result[0] == expected[0]);
    }

    // Test case 5: Large arrays
    {
        const int size = 1000;
        double a[size], b[size], result[size], expected[size];
        
        for (int i = 0; i < size; ++i) {
            a[i] = i * 1.5;
            b[i] = i * 0.5;
            expected[i] = a[i] - b[i];
        }
        
        doubleArrayVectorSubtract(a, b, result, size);
        
        for (int i = 0; i < size; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 6: Zero-length array (should do nothing)
    {
        double a[] = {1.0, 2.0, 3.0};
        double b[] = {1.0, 2.0, 3.0};
        double result[] = {0.0, 0.0, 0.0};
        double original_result[] = {0.0, 0.0, 0.0};
        
        doubleArrayVectorSubtract(a, b, result, 0);
        
        for (int i = 0; i < 3; ++i) {
            assert(result[i] == original_result[i]);
        }
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

void doubleArrayVectorSubtract(double* d_in_a, double* d_in_b, double* d_out, int length) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in_a[tid] - d_in_b[tid];
    }
}