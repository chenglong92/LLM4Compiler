// original code(id = 166): 
 /*
__global__ void MatrixMulKernel ( float * Md , float * Nd , float * Pd , int width ) { int tx = threadIdx . x ; int ty = threadIdx . y ; float pvalue = 0 ; for ( int k = 0 ; k < width ; ++ k ) { float Mdelement = Md [ ty * width + k ] ; float Ndelement = Nd [ ty * width + k ] ; pvalue += Mdelement * Ndelement ; } Pd [ ty * width + tx ] = pvalue ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width) {
    for (int ty = 0; ty < width; ++ty) {
        for (int tx = 0; tx < width; ++tx) {
            float pvalue = 0;
            for (int k = 0; k < width; ++k) {
                float Mdelement = Md[ty * width + k];
                float Ndelement = Nd[k * width + tx];
                pvalue += Mdelement * Ndelement;
            }
            Pd[ty * width + tx] = pvalue;
        }
    }
}

void testMatrixMultiplication() {
    // Test case 1: 2x2 matrices
    {
        float A[] = {1, 2, 3, 4};
        float B[] = {5, 6, 7, 8};
        float expected[] = {19, 22, 43, 50};
        float result[4];
        
        MatrixMulKernel(A, B, result, 2);
        
        for (int i = 0; i < 4; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 2: 3x3 matrices
    {
        float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        float B[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        float expected[] = {30, 24, 18, 84, 69, 54, 138, 114, 90};
        float result[9];
        
        MatrixMulKernel(A, B, result, 3);
        
        for (int i = 0; i < 9; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 3: Identity matrix multiplication
    {
        float A[] = {1, 2, 3, 4};
        float I[] = {1, 0, 0, 1};
        float expected[] = {1, 2, 3, 4};
        float result[4];
        
        MatrixMulKernel(A, I, result, 2);
        
        for (int i = 0; i < 4; ++i) {
            assert(result[i] == expected[i]);
        }
    }

    // Test case 4: Zero matrix multiplication
    {
        float A[] = {1, 2, 3, 4};
        float Z[] = {0, 0, 0, 0};
        float expected[] = {0, 0, 0, 0};
        float result[4];
        
        MatrixMulKernel(A, Z, result, 2);
        
        for (int i = 0; i < 4; ++i) {
            assert(result[i] == expected[i]);
        }
    }
}

int main() {
    testMatrixMultiplication();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}