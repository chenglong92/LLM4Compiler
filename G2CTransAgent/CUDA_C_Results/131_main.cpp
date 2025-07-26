// original code(id = 131): 
 /*
__global__ void deinter_kernel ( int NX , float * X , int NY , float * Y , int B , float * OUT ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < ( NX + NY ) * B ) { int b = i / ( NX + NY ) ; int j = i % ( NX + NY ) ; if ( j < NX ) { if ( X ) X [ b * NX + j ] += OUT [ i ] ; } else { if ( Y ) Y [ b * NY + j - NX ] += OUT [ i ] ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void deinter_kernel(int NX, float* X, int NY, float* Y, int B, float* OUT) {
    for (int i = 0; i < (NX + NY) * B; ++i) {
        int b = i / (NX + NY);
        int j = i % (NX + NY);
        if (j < NX) {
            if (X) X[b * NX + j] += OUT[i];
        } else {
            if (Y) Y[b * NY + (j - NX)] += OUT[i];
        }
    }
}

int main() {
    // Test case 1: Normal case with non-null X and Y
    {
        int NX = 4, NY = 3, B = 2;
        float *X = new float[NX * B]();
        float *Y = new float[NY * B]();
        float *OUT = new float[(NX + NY) * B];
        
        for (int i = 0; i < (NX + NY) * B; ++i) {
            OUT[i] = static_cast<float>(i + 1);
        }
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // Verify X values
        assert(X[0] == 1.0f);
        assert(X[1] == 2.0f);
        assert(X[2] == 3.0f);
        assert(X[3] == 4.0f);
        assert(X[4] == 8.0f);
        assert(X[5] == 9.0f);
        assert(X[6] == 10.0f);
        assert(X[7] == 11.0f);
        
        // Verify Y values
        assert(Y[0] == 5.0f);
        assert(Y[1] == 6.0f);
        assert(Y[2] == 7.0f);
        assert(Y[3] == 12.0f);
        assert(Y[4] == 13.0f);
        assert(Y[5] == 14.0f);
        
        delete[] X;
        delete[] Y;
        delete[] OUT;
    }
    
    // Test case 2: Edge case with null X
    {
        int NX = 2, NY = 2, B = 1;
        float *X = nullptr;
        float *Y = new float[NY * B]();
        float *OUT = new float[(NX + NY) * B];
        
        for (int i = 0; i < (NX + NY) * B; ++i) {
            OUT[i] = static_cast<float>(i + 1);
        }
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // Verify Y values (X should remain unchanged as it's null)
        assert(Y[0] == 3.0f);
        assert(Y[1] == 4.0f);
        
        delete[] Y;
        delete[] OUT;
    }
    
    // Test case 3: Edge case with null Y
    {
        int NX = 3, NY = 1, B = 2;
        float *X = new float[NX * B]();
        float *Y = nullptr;
        float *OUT = new float[(NX + NY) * B];
        
        for (int i = 0; i < (NX + NY) * B; ++i) {
            OUT[i] = static_cast<float>(i + 1);
        }
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // Verify X values (Y should remain unchanged as it's null)
        assert(X[0] == 1.0f);
        assert(X[1] == 2.0f);
        assert(X[2] == 3.0f);
        assert(X[3] == 5.0f);
        assert(X[4] == 6.0f);
        assert(X[5] == 7.0f);
        
        delete[] X;
        delete[] OUT;
    }
    
    // Test case 4: Edge case with B = 0 (should do nothing)
    {
        int NX = 2, NY = 2, B = 0;
        float *X = new float[NX * B]();
        float *Y = new float[NY * B]();
        float *OUT = new float[(NX + NY) * B];
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // No assertions as nothing should happen
        
        delete[] X;
        delete[] Y;
        delete[] OUT;
    }
    
    // Test case 5: Edge case with NX = 0
    {
        int NX = 0, NY = 3, B = 2;
        float *X = nullptr;
        float *Y = new float[NY * B]();
        float *OUT = new float[(NX + NY) * B];
        
        for (int i = 0; i < (NX + NY) * B; ++i) {
            OUT[i] = static_cast<float>(i + 1);
        }
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // Verify Y values (all OUT should go to Y)
        assert(Y[0] == 1.0f);
        assert(Y[1] == 2.0f);
        assert(Y[2] == 3.0f);
        assert(Y[3] == 4.0f);
        assert(Y[4] == 5.0f);
        assert(Y[5] == 6.0f);
        
        delete[] Y;
        delete[] OUT;
    }
    
    // Test case 6: Edge case with NY = 0
    {
        int NX = 2, NY = 0, B = 1;
        float *X = new float[NX * B]();
        float *Y = nullptr;
        float *OUT = new float[(NX + NY) * B];
        
        for (int i = 0; i < (NX + NY) * B; ++i) {
            OUT[i] = static_cast<float>(i + 1);
        }
        
        deinter_kernel(NX, X, NY, Y, B, OUT);
        
        // Verify X values (all OUT should go to X)
        assert(X[0] == 1.0f);
        assert(X[1] == 2.0f);
        
        delete[] X;
        delete[] OUT;
    }
    
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}