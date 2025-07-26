// original code(id = 232): 
 /*
__global__ void doubleArrayScalarAddKernel ( double * d_in , double * d_out , int length , double scalar ) { int tid = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( tid < length ) { d_out [ tid ] = d_in [ tid ] + scalar ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void doubleArrayScalarAdd(double* d_in, double* d_out, int length, double scalar) {
    for (int tid = 0; tid < length; ++tid) {
        d_out[tid] = d_in[tid] + scalar;
    }
}

int main() {
    // Test case 1: Normal case with positive numbers
    {
        double in[] = {1.0, 2.0, 3.0, 4.0};
        double out[4];
        double scalar = 5.0;
        double expected[] = {6.0, 7.0, 8.0, 9.0};
        doubleArrayScalarAdd(in, out, 4, scalar);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 2: Normal case with negative numbers
    {
        double in[] = {-1.0, -2.0, -3.0, -4.0};
        double out[4];
        double scalar = -5.0;
        double expected[] = {-6.0, -7.0, -8.0, -9.0};
        doubleArrayScalarAdd(in, out, 4, scalar);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    // Test case 3: Edge case with zero length
    {
        double in[] = {1.0, 2.0, 3.0};
        double out[3];
        double scalar = 5.0;
        doubleArrayScalarAdd(in, out, 0, scalar); // Should do nothing
        // No assertion as function should handle zero length gracefully
    }

    // Test case 4: Edge case with large array
    {
        const int large_length = 1000000;
        double* in = new double[large_length];
        double* out = new double[large_length];
        double scalar = 10.0;
        for (int i = 0; i < large_length; ++i) {
            in[i] = static_cast<double>(i);
        }
        doubleArrayScalarAdd(in, out, large_length, scalar);
        for (int i = 0; i < large_length; ++i) {
            assert(out[i] == in[i] + scalar);
        }
        delete[] in;
        delete[] out;
    }

    // Test case 5: Mixed positive and negative numbers with zero scalar
    {
        double in[] = {-1.5, 0.0, 3.7, -2.3};
        double out[4];
        double scalar = 0.0;
        double expected[] = {-1.5, 0.0, 3.7, -2.3};
        doubleArrayScalarAdd(in, out, 4, scalar);
        for (int i = 0; i < 4; ++i) {
            assert(out[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}