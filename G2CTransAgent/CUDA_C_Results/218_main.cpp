// original code(id = 218): 
 /*
__global__ void vectorDiv ( const float * A , const float * B , float * C , int numElements ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i < numElements ) { C [ i ] = A [ i ] / B [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void vectorDiv(const float* A, const float* B, float* C, int numElements) {
    for (int i = 0; i < numElements; ++i) {
        C[i] = A[i] / B[i];
    }
}

int main() {
    // Test case 1: Normal case with positive numbers
    {
        const int numElements = 5;
        float A[numElements] = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f};
        float B[numElements] = {2.0f, 4.0f, 5.0f, 8.0f, 10.0f};
        float C[numElements] = {0.0f};
        
        vectorDiv(A, B, C, numElements);
        
        assert(C[0] == 5.0f);
        assert(C[1] == 5.0f);
        assert(C[2] == 6.0f);
        assert(C[3] == 5.0f);
        assert(C[4] == 5.0f);
    }

    // Test case 2: Normal case with mixed positive and negative numbers
    {
        const int numElements = 4;
        float A[numElements] = {-10.0f, 20.0f, -30.0f, 40.0f};
        float B[numElements] = {2.0f, -4.0f, 5.0f, -8.0f};
        float C[numElements] = {0.0f};
        
        vectorDiv(A, B, C, numElements);
        
        assert(C[0] == -5.0f);
        assert(C[1] == -5.0f);
        assert(C[2] == -6.0f);
        assert(C[3] == -5.0f);
    }

    // Test case 3: Edge case with division by very small number (near zero)
    {
        const int numElements = 3;
        float A[numElements] = {1.0f, 2.0f, 3.0f};
        float B[numElements] = {0.0001f, 0.0002f, 0.0003f};
        float C[numElements] = {0.0f};
        
        vectorDiv(A, B, C, numElements);
        
        assert(C[0] == 10000.0f);
        assert(C[1] == 10000.0f);
        assert(C[2] == 10000.0f);
    }

    // Test case 4: Edge case with zero elements (should do nothing)
    {
        const int numElements = 0;
        float A[1] = {1.0f};  // Dummy data
        float B[1] = {2.0f};  // Dummy data
        float C[1] = {0.0f};  // Dummy data
        
        vectorDiv(A, B, C, numElements);
        
        // No assertions since nothing should happen
    }

    // Note: Division by zero is undefined behavior, so we don't test it here

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}