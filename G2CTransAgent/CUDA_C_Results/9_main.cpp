// original code(id = 9): 
 /*
__global__ void doubleArrayScalarDivideKernel ( double * d_in , int * d_out , int length , double scalar ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = ( int ) ( d_in [ tid ] / scalar ) ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void doubleArrayScalarDivide(double* d_in, int* d_out, int length, double scalar) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = static_cast<int>(d_in[tid] / scalar);
    }
}

int main() {
    // Test case 1: Normal case with positive scalar
    {
        double input1[] = {10.0, 20.0, 30.0, 40.0};
        int output1[4];
        double scalar1 = 2.0;
        doubleArrayScalarDivide(input1, output1, 4, scalar1);
        assert(output1[0] == 5);
        assert(output1[1] == 10);
        assert(output1[2] == 15);
        assert(output1[3] == 20);
    }

    // Test case 2: Normal case with negative scalar
    {
        double input2[] = {10.0, 20.0, 30.0, 40.0};
        int output2[4];
        double scalar2 = -2.0;
        doubleArrayScalarDivide(input2, output2, 4, scalar2);
        assert(output2[0] == -5);
        assert(output2[1] == -10);
        assert(output2[2] == -15);
        assert(output2[3] == -20);
    }

    // Test case 3: Scalar is zero (division by zero, undefined behavior expected)
    {
        double input3[] = {10.0, 20.0, 30.0, 40.0};
        int output3[4];
        double scalar3 = 0.0;
        // Note: This will cause undefined behavior, but we include it as an edge case
        doubleArrayScalarDivide(input3, output3, 4, scalar3);
    }

    // Test case 4: Empty array
    {
        double input4[] = {};
        int output4[0];
        double scalar4 = 2.0;
        doubleArrayScalarDivide(input4, output4, 0, scalar4);
    }

    // Test case 5: Scalar is very small
    {
        double input5[] = {1.0, 2.0, 3.0, 4.0};
        int output5[4];
        double scalar5 = 1e-10;
        doubleArrayScalarDivide(input5, output5, 4, scalar5);
        assert(output5[0] == static_cast<int>(1.0 / scalar5));
        assert(output5[1] == static_cast<int>(2.0 / scalar5));
        assert(output5[2] == static_cast<int>(3.0 / scalar5));
        assert(output5[3] == static_cast<int>(4.0 / scalar5));
    }

    // Test case 6: Scalar is very large
    {
        double input6[] = {1.0, 2.0, 3.0, 4.0};
        int output6[4];
        double scalar6 = 1e10;
        doubleArrayScalarDivide(input6, output6, 4, scalar6);
        assert(output6[0] == 0);
        assert(output6[1] == 0);
        assert(output6[2] == 0);
        assert(output6[3] == 0);
    }

    // Test case 7: Mixed positive and negative input values
    {
        double input7[] = {-10.0, 20.0, -30.0, 40.0};
        int output7[4];
        double scalar7 = 2.0;
        doubleArrayScalarDivide(input7, output7, 4, scalar7);
        assert(output7[0] == -5);
        assert(output7[1] == 10);
        assert(output7[2] == -15);
        assert(output7[3] == 20);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}