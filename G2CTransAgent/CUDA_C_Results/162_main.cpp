// original code(id = 162): 
 /*
__global__ void Init ( const long long size , const double * in , double * out ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < size ) out [ i ] = in [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void Init(const long long size, const double* in, double* out) {
    for (int i = 0; i < size; ++i) {
        out[i] = in[i];
    }
}

int main() {
    // Test case 1: Normal case with positive size
    {
        const long long size = 5;
        double in[] = {1.1, 2.2, 3.3, 4.4, 5.5};
        double out[size];
        Init(size, in, out);
        for (int i = 0; i < size; ++i) {
            assert(out[i] == in[i]);
        }
    }

    // Test case 2: Edge case with size 0
    {
        const long long size = 0;
        double in[] = {};
        double out[size];
        Init(size, in, out);
        // No assertion needed as no elements to copy
    }

    // Test case 3: Edge case with size 1
    {
        const long long size = 1;
        double in[] = {42.0};
        double out[size];
        Init(size, in, out);
        assert(out[0] == in[0]);
    }

    // Test case 4: Large size
    {
        const long long size = 1000000;
        double* in = new double[size];
        double* out = new double[size];
        for (long long i = 0; i < size; ++i) {
            in[i] = i * 1.1;
        }
        Init(size, in, out);
        for (long long i = 0; i < size; ++i) {
            assert(out[i] == in[i]);
        }
        delete[] in;
        delete[] out;
    }

    // Test case 5: Negative size (should not be possible as size is long long)
    // Not applicable as size is unsigned in practice (though parameter is long long)

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}