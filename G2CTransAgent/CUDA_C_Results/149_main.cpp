// original code(id = 149): 
 /*
__global__ void vectorAdd ( const float * A , const float * B , float * C , int numElements ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i < numElements ) { C [ i ] = A [ i ] + B [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <vector>
#include <limits>

void vectorAdd(const float* A, const float* B, float* C, int numElements) {
    for (int i = 0; i < numElements; ++i) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    // Test case 1: Basic addition with positive numbers
    {
        const int numElements = 3;
        float A[numElements] = {1.0f, 2.0f, 3.0f};
        float B[numElements] = {4.0f, 5.0f, 6.0f};
        float C[numElements] = {0.0f};
        
        vectorAdd(A, B, C, numElements);
        
        assert(C[0] == 5.0f);
        assert(C[1] == 7.0f);
        assert(C[2] == 9.0f);
    }

    // Test case 2: Addition with negative numbers
    {
        const int numElements = 4;
        float A[numElements] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float B[numElements] = {1.0f, 2.0f, 3.0f, 4.0f};
        float C[numElements] = {0.0f};
        
        vectorAdd(A, B, C, numElements);
        
        assert(C[0] == 0.0f);
        assert(C[1] == 0.0f);
        assert(C[2] == 0.0f);
        assert(C[3] == 0.0f);
    }

    // Test case 3: Addition with zero elements (edge case)
    {
        const int numElements = 0;
        float A[1] = {1.0f};  // Dummy data
        float B[1] = {2.0f};  // Dummy data
        float C[1] = {0.0f};  // Dummy data
        
        vectorAdd(A, B, C, numElements);
        
        // No assertions needed as function shouldn't modify anything
    }

    // Test case 4: Addition with large numbers
    {
        const int numElements = 2;
        float A[numElements] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        float B[numElements] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        float C[numElements] = {0.0f};
        
        vectorAdd(A, B, C, numElements);
        
        assert(C[0] == std::numeric_limits<float>::infinity());
        assert(C[1] == std::numeric_limits<float>::infinity());
    }

    // Test case 5: Addition with very small numbers
    {
        const int numElements = 2;
        float A[numElements] = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
        float B[numElements] = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
        float C[numElements] = {0.0f};
        
        vectorAdd(A, B, C, numElements);
        
        assert(C[0] == 2 * std::numeric_limits<float>::min());
        assert(C[1] == 2 * std::numeric_limits<float>::min());
    }

    // Test case 6: Addition with mixed positive and negative numbers
    {
        const int numElements = 5;
        float A[numElements] = {1.5f, -2.5f, 0.0f, -0.0f, 100.0f};
        float B[numElements] = {-1.5f, 2.5f, 0.0f, 0.0f, -50.0f};
        float C[numElements] = {0.0f};
        
        vectorAdd(A, B, C, numElements);
        
        assert(C[0] == 0.0f);
        assert(C[1] == 0.0f);
        assert(C[2] == 0.0f);
        assert(C[3] == 0.0f);
        assert(C[4] == 50.0f);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}