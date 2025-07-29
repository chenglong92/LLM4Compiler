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
    // Test case 1: Normal case with positive values
    {
        double input1[] = {10.5, 20.25, 30.75, 40.0};
        int output1[4];
        double scalar1 = 2.5;
        int expected1[] = {4, 8, 12, 16};
        
        doubleArrayScalarDivide(input1, output1, 4, scalar1);
        
        for (int i = 0; i < 4; ++i) {
            assert(output1[i] == expected1[i]);
        }
    }

    // Test case 2: Normal case with negative values
    {
        double input2[] = {-10.5, -20.25, -30.75, -40.0};
        int output2[4];
        double scalar2 = 2.5;
        int expected2[] = {-4, -8, -12, -16};
        
        doubleArrayScalarDivide(input2, output2, 4, scalar2);
        
        for (int i = 0; i < 4; ++i) {
            assert(output2[i] == expected2[i]);
        }
    }

    // Test case 3: Mixed positive and negative values
    {
        double input3[] = {10.5, -20.25, 30.75, -40.0};
        int output3[4];
        double scalar3 = 2.5;
        int expected3[] = {4, -8, 12, -16};
        
        doubleArrayScalarDivide(input3, output3, 4, scalar3);
        
        for (int i = 0; i < 4; ++i) {
            assert(output3[i] == expected3[i]);
        }
    }

    // Test case 4: Scalar is 1.0 (identity operation)
    {
        double input4[] = {1.1, 2.2, 3.3, 4.4};
        int output4[4];
        double scalar4 = 1.0;
        int expected4[] = {1, 2, 3, 4};
        
        doubleArrayScalarDivide(input4, output4, 4, scalar4);
        
        for (int i = 0; i < 4; ++i) {
            assert(output4[i] == expected4[i]);
        }
    }

    // Test case 5: Scalar is negative
    {
        double input5[] = {10.5, 20.25, 30.75, 40.0};
        int output5[4];
        double scalar5 = -2.5;
        int expected5[] = {-4, -8, -12, -16};
        
        doubleArrayScalarDivide(input5, output5, 4, scalar5);
        
        for (int i = 0; i < 4; ++i) {
            assert(output5[i] == expected5[i]);
        }
    }

    // Test case 6: Scalar is zero (division by zero - undefined behavior, but should compile)
    {
        double input6[] = {10.5, 20.25, 30.75, 40.0};
        int output6[4];
        double scalar6 = 0.0;
        
        // Note: This will cause undefined behavior, but we're just testing compilation
        doubleArrayScalarDivide(input6, output6, 4, scalar6);
    }

    // Test case 7: Empty array
    {
        double input7[] = {};
        int output7[0];
        double scalar7 = 2.5;
        
        doubleArrayScalarDivide(input7, output7, 0, scalar7);
    }

    // Test case 8: Large values
    {
        double input8[] = {1e20, 2e20, 3e20};
        int output8[3];
        double scalar8 = 1e19;
        int expected8[] = {10, 20, 30};
        
        doubleArrayScalarDivide(input8, output8, 3, scalar8);
        
        for (int i = 0; i < 3; ++i) {
            assert(output8[i] == expected8[i]);
        }
    }

    // Test case 9: Small values
    {
        double input9[] = {1e-20, 2e-20, 3e-20};
        int output9[3];
        double scalar9 = 1e-19;
        int expected9[] = {0, 0, 0}; // Results will be 0.1, 0.2, 0.3 which cast to 0
        
        doubleArrayScalarDivide(input9, output9, 3, scalar9);
        
        for (int i = 0; i < 3; ++i) {
            assert(output9[i] == expected9[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}