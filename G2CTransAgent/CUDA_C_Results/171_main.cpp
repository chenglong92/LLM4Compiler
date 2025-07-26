// original code(id = 171): 
 /*
__global__ void vectorAdd ( double * a , double * b , double * c , int vector_size ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < vector_size ) { c [ tid ] = a [ tid ] + b [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void vectorAdd(double* a, double* b, double* c, int vector_size) {
    for (int tid = 0; tid < vector_size; ++tid) {
        c[tid] = a[tid] + b[tid];
    }
}

void testVectorAdd() {
    // Test case 1: Basic addition
    {
        double a[] = {1.0, 2.0, 3.0};
        double b[] = {4.0, 5.0, 6.0};
        double c[3];
        vectorAdd(a, b, c, 3);
        assert(c[0] == 5.0);
        assert(c[1] == 7.0);
        assert(c[2] == 9.0);
    }

    // Test case 2: Empty vectors
    {
        double a[] = {};
        double b[] = {};
        double c[0];
        vectorAdd(a, b, c, 0);
        // No elements to check
    }

    // Test case 3: Negative numbers
    {
        double a[] = {-1.0, -2.0, -3.0};
        double b[] = {1.0, 2.0, 3.0};
        double c[3];
        vectorAdd(a, b, c, 3);
        assert(c[0] == 0.0);
        assert(c[1] == 0.0);
        assert(c[2] == 0.0);
    }

    // Test case 4: Large numbers
    {
        double a[] = {1.0e20, 2.0e20, 3.0e20};
        double b[] = {1.0e20, 2.0e20, 3.0e20};
        double c[3];
        vectorAdd(a, b, c, 3);
        assert(c[0] == 2.0e20);
        assert(c[1] == 4.0e20);
        assert(c[2] == 6.0e20);
    }

    // Test case 5: Single element
    {
        double a[] = {42.0};
        double b[] = {58.0};
        double c[1];
        vectorAdd(a, b, c, 1);
        assert(c[0] == 100.0);
    }

    // Test case 6: Floating point precision
    {
        double a[] = {0.1, 0.2, 0.3};
        double b[] = {0.4, 0.5, 0.6};
        double c[3];
        vectorAdd(a, b, c, 3);
        assert(c[0] == 0.5);
        assert(c[1] == 0.7);
        assert(c[2] == 0.9);
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testVectorAdd();
    return 0;
}