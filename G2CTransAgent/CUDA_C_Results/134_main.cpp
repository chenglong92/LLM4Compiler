// original code(id = 134): 
 /*
__global__ void doubleArrayScalarSubtractKernel ( double * d_in , double * d_out , int length , double scalar ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in [ tid ] - scalar ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void doubleArrayScalarSubtract(double* d_in, double* d_out, int length, double scalar) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in[tid] - scalar;
    }
}

int main() {
    // Test case 1: Normal case with positive numbers
    {
        double in[] = {1.0, 2.0, 3.0, 4.0};
        double out[4];
        double expected[] = {0.0, 1.0, 2.0, 3.0};
        doubleArrayScalarSubtract(in, out, 4, 1.0);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 2: Normal case with negative numbers
    {
        double in[] = {-1.0, -2.0, -3.0, -4.0};
        double out[4];
        double expected[] = {-2.0, -3.0, -4.0, -5.0};
        doubleArrayScalarSubtract(in, out, 4, 1.0);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 3: Case with zero scalar
    {
        double in[] = {1.5, 2.5, 3.5, 4.5};
        double out[4];
        double expected[] = {1.5, 2.5, 3.5, 4.5};
        doubleArrayScalarSubtract(in, out, 4, 0.0);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 4: Case with empty array
    {
        double in[] = {};
        double out[] = {};
        doubleArrayScalarSubtract(in, out, 0, 1.0);
        // No assertion needed as the function should handle length 0
    }

    // Test case 5: Case with mixed positive and negative numbers
    {
        double in[] = {-1.0, 2.0, -3.0, 4.0};
        double out[4];
        double expected[] = {-3.0, 0.0, -5.0, 2.0};
        doubleArrayScalarSubtract(in, out, 4, 2.0);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 6: Case with large array
    {
        const int large_size = 10000;
        double* in = new double[large_size];
        double* out = new double[large_size];
        double* expected = new double[large_size];
        
        for (int i = 0; i < large_size; ++i) {
            in[i] = i * 1.5;
            expected[i] = in[i] - 2.5;
        }
        
        doubleArrayScalarSubtract(in, out, large_size, 2.5);
        
        for (int i = 0; i < large_size; ++i) {
            assert(out[i] == expected[i]);
        }
        
        delete[] in;
        delete[] out;
        delete[] expected;
    }

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}