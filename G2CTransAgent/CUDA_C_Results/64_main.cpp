// original code(id = 64): 
 /*
__global__ void saxpy_gpu ( float * vecY , float * vecX , float alpha , int n ) { int x , y , i ; x = blockIdx . x * blockDim . x + threadIdx . x ; y = blockIdx . y * blockDim . y + threadIdx . y ; i = y * 1024 + x ; if ( i < n ) vecY [ i ] = alpha * vecX [ i ] + vecY [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void saxpy_cpu(float* vecY, float* vecX, float alpha, int n) {
    for (int i = 0; i < n; i++) {
        vecY[i] = alpha * vecX[i] + vecY[i];
    }
}

void test_saxpy_cpu() {
    // Test case 1: Basic test with positive values
    {
        float vecX[] = {1.0f, 2.0f, 3.0f};
        float vecY[] = {4.0f, 5.0f, 6.0f};
        float alpha = 2.0f;
        int n = 3;
        
        float expected[] = {6.0f, 9.0f, 12.0f};
        saxpy_cpu(vecY, vecX, alpha, n);
        
        for (int i = 0; i < n; i++) {
            assert(vecY[i] == expected[i]);
        }
    }

    // Test case 2: Test with alpha = 0
    {
        float vecX[] = {1.0f, 2.0f, 3.0f};
        float vecY[] = {4.0f, 5.0f, 6.0f};
        float alpha = 0.0f;
        int n = 3;
        
        float expected[] = {4.0f, 5.0f, 6.0f};
        saxpy_cpu(vecY, vecX, alpha, n);
        
        for (int i = 0; i < n; i++) {
            assert(vecY[i] == expected[i]);
        }
    }

    // Test case 3: Test with negative alpha
    {
        float vecX[] = {1.0f, 2.0f, 3.0f};
        float vecY[] = {4.0f, 5.0f, 6.0f};
        float alpha = -1.0f;
        int n = 3;
        
        float expected[] = {3.0f, 3.0f, 3.0f};
        saxpy_cpu(vecY, vecX, alpha, n);
        
        for (int i = 0; i < n; i++) {
            assert(vecY[i] == expected[i]);
        }
    }

    // Test case 4: Test with negative values in vectors
    {
        float vecX[] = {-1.0f, -2.0f, -3.0f};
        float vecY[] = {4.0f, 5.0f, 6.0f};
        float alpha = 2.0f;
        int n = 3;
        
        float expected[] = {2.0f, 1.0f, 0.0f};
        saxpy_cpu(vecY, vecX, alpha, n);
        
        for (int i = 0; i < n; i++) {
            assert(vecY[i] == expected[i]);
        }
    }

    // Test case 5: Test with single element
    {
        float vecX[] = {5.0f};
        float vecY[] = {10.0f};
        float alpha = 0.5f;
        int n = 1;
        
        float expected[] = {12.5f};
        saxpy_cpu(vecY, vecX, alpha, n);
        
        assert(vecY[0] == expected[0]);
    }

    // Test case 6: Test with large n
    {
        const int n = 1000;
        float vecX[n];
        float vecY[n];
        float alpha = 1.5f;
        
        for (int i = 0; i < n; i++) {
            vecX[i] = static_cast<float>(i);
            vecY[i] = static_cast<float>(n - i);
        }
        
        saxpy_cpu(vecY, vecX, alpha, n);
        
        for (int i = 0; i < n; i++) {
            float expected = 1.5f * vecX[i] + (n - i);
            assert(vecY[i] == expected);
        }
    }
}

int main() {
    test_saxpy_cpu();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}