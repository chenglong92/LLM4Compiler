// original code(id = 178): 
 /*
__global__ void SetToZero_kernel ( float * d_vx , float * d_vy , float * d_vz , int w , int h , int l ) { unsigned int i = blockIdx . x * blockDim . x + threadIdx . x ; unsigned int j = blockIdx . y * blockDim . y + threadIdx . y ; unsigned int index = j * w + i ; if ( i < w && j < h ) { for ( int k = 0 ; k < l ; ++ k , index += w * h ) { d_vx [ index ] = 0 ; d_vy [ index ] = 0 ; d_vz [ index ] = 0 ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void SetToZero(float* d_vx, float* d_vy, float* d_vz, int w, int h, int l);

int main() {
    // Test Case 1: Normal case with small dimensions
    {
        const int w = 2, h = 2, l = 2;
        const int size = w * h * l;
        float vx[size], vy[size], vz[size];
        
        // Initialize with non-zero values
        for (int i = 0; i < size; ++i) {
            vx[i] = 1.0f;
            vy[i] = 2.0f;
            vz[i] = 3.0f;
        }
        
        SetToZero(vx, vy, vz, w, h, l);
        
        // Verify all elements are zero
        for (int i = 0; i < size; ++i) {
            assert(vx[i] == 0.0f);
            assert(vy[i] == 0.0f);
            assert(vz[i] == 0.0f);
        }
    }

    // Test Case 2: Boundary case with minimum dimensions (1x1x1)
    {
        const int w = 1, h = 1, l = 1;
        const int size = w * h * l;
        float vx[size], vy[size], vz[size];
        
        vx[0] = 5.0f;
        vy[0] = 6.0f;
        vz[0] = 7.0f;
        
        SetToZero(vx, vy, vz, w, h, l);
        
        assert(vx[0] == 0.0f);
        assert(vy[0] == 0.0f);
        assert(vz[0] == 0.0f);
    }

    // Test Case 3: Larger dimensions
    {
        const int w = 10, h = 10, l = 10;
        const int size = w * h * l;
        float* vx = new float[size];
        float* vy = new float[size];
        float* vz = new float[size];
        
        // Initialize with non-zero values
        for (int i = 0; i < size; ++i) {
            vx[i] = 1.5f;
            vy[i] = 2.5f;
            vz[i] = 3.5f;
        }
        
        SetToZero(vx, vy, vz, w, h, l);
        
        // Verify all elements are zero
        for (int i = 0; i < size; ++i) {
            assert(vx[i] == 0.0f);
            assert(vy[i] == 0.0f);
            assert(vz[i] == 0.0f);
        }
        
        delete[] vx;
        delete[] vy;
        delete[] vz;
    }

    // Test Case 4: Zero dimensions (should handle gracefully)
    {
        const int w = 0, h = 0, l = 0;
        float* vx = nullptr;
        float* vy = nullptr;
        float* vz = nullptr;
        
        SetToZero(vx, vy, vz, w, h, l);
        // No assertion as function should handle gracefully
    }

    // Test Case 5: Mixed dimensions (w != h != l)
    {
        const int w = 3, h = 4, l = 5;
        const int size = w * h * l;
        float vx[size], vy[size], vz[size];
        
        // Initialize with non-zero values
        for (int i = 0; i < size; ++i) {
            vx[i] = 0.5f;
            vy[i] = 1.5f;
            vz[i] = 2.5f;
        }
        
        SetToZero(vx, vy, vz, w, h, l);
        
        // Verify all elements are zero
        for (int i = 0; i < size; ++i) {
            assert(vx[i] == 0.0f);
            assert(vy[i] == 0.0f);
            assert(vz[i] == 0.0f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void SetToZero(float* d_vx, float* d_vy, float* d_vz, int w, int h, int l) {
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            unsigned int index = j * w + i;
            for (int k = 0; k < l; ++k, index += w * h) {
                d_vx[index] = 0;
                d_vy[index] = 0;
                d_vz[index] = 0;
            }
        }
    }
}