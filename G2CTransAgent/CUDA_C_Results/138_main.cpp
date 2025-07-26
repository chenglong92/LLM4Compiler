// original code(id = 138): 
 /*
__global__ void cuda_laplace_filter ( float * Img , float * laplace , float _dz , float _dx , int npml , int nnz , int nnx ) { int i1 = threadIdx . x + blockDim . x * blockIdx . x ; int i2 = threadIdx . y + blockDim . y * blockIdx . y ; int id = i1 + i2 * nnz ; float diff1 = 0.0f ; float diff2 = 0.0f ; if ( i1 >= npml && i1 < nnz - npml && i2 >= npml && i2 < nnx - npml ) { diff1 = Img [ id + 1 ] - 2.0 * Img [ id ] + Img [ id - 1 ] ; diff2 = Img [ id + nnz ] - 2.0 * Img [ id ] + Img [ id - nnz ] ; } laplace [ id ] = _dz * _dz * diff1 + _dx * _dx * diff2 ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void cuda_laplace_filter(float* Img, float* laplace, float _dz, float _dx, int npml, int nnz, int nnx) {
    for (int i2 = 0; i2 < nnx; ++i2) {
        for (int i1 = 0; i1 < nnz; ++i1) {
            int id = i1 + i2 * nnz;
            float diff1 = 0.0f;
            float diff2 = 0.0f;
            
            if (i1 >= npml && i1 < nnz - npml && i2 >= npml && i2 < nnx - npml) {
                diff1 = Img[id + 1] - 2.0f * Img[id] + Img[id - 1];
                diff2 = Img[id + nnz] - 2.0f * Img[id] + Img[id - nnz];
            }
            
            laplace[id] = _dz * _dz * diff1 + _dx * _dx * diff2;
        }
    }
}

int main() {
    // Test case 1: Small array with npml = 1
    {
        const int npml = 1;
        const int nnz = 3;
        const int nnx = 3;
        const float _dz = 1.0f;
        const float _dx = 1.0f;
        
        float Img[nnz * nnx] = {1.0f, 2.0f, 3.0f,
                                4.0f, 5.0f, 6.0f,
                                7.0f, 8.0f, 9.0f};
        float laplace[nnz * nnx] = {0};
        
        cuda_laplace_filter(Img, laplace, _dz, _dx, npml, nnz, nnx);
        
        // Check center element (should be processed)
        assert(laplace[4] == (1.0f*(6.0f-2*5.0f+4.0f) + 1.0f*(8.0f-2*5.0f+2.0f)));
        
        // Check boundary elements (should be 0)
        assert(laplace[0] == 0.0f);
        assert(laplace[2] == 0.0f);
        assert(laplace[6] == 0.0f);
        assert(laplace[8] == 0.0f);
    }
    
    // Test case 2: Larger array with npml = 2
    {
        const int npml = 2;
        const int nnz = 5;
        const int nnx = 5;
        const float _dz = 0.5f;
        const float _dx = 0.25f;
        
        float Img[nnz * nnx] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
                                6.0f, 7.0f, 8.0f, 9.0f, 10.0f,
                                11.0f, 12.0f, 13.0f, 14.0f, 15.0f,
                                16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                21.0f, 22.0f, 23.0f, 24.0f, 25.0f};
        float laplace[nnz * nnx] = {0};
        
        cuda_laplace_filter(Img, laplace, _dz, _dx, npml, nnz, nnx);
        
        // Check center element (should be processed)
        assert(laplace[12] == (0.25f*(13.0f-2*12.0f+11.0f) + 0.0625f*(17.0f-2*12.0f+7.0f)));
        
        // Check boundary elements (should be 0)
        assert(laplace[0] == 0.0f);
        assert(laplace[4] == 0.0f);
        assert(laplace[20] == 0.0f);
        assert(laplace[24] == 0.0f);
    }
    
    // Test case 3: All elements in PML (npml larger than half dimensions)
    {
        const int npml = 3;
        const int nnz = 4;
        const int nnx = 4;
        const float _dz = 1.0f;
        const float _dx = 1.0f;
        
        float Img[nnz * nnx] = {1.0f, 2.0f, 3.0f, 4.0f,
                                5.0f, 6.0f, 7.0f, 8.0f,
                                9.0f, 10.0f, 11.0f, 12.0f,
                                13.0f, 14.0f, 15.0f, 16.0f};
        float laplace[nnz * nnx] = {0};
        
        cuda_laplace_filter(Img, laplace, _dz, _dx, npml, nnz, nnx);
        
        // All elements should be 0 since npml is too large
        for (int i = 0; i < nnz * nnx; ++i) {
            assert(laplace[i] == 0.0f);
        }
    }
    
    // Test case 4: Single non-PML element
    {
        const int npml = 1;
        const int nnz = 3;
        const int nnx = 3;
        const float _dz = 2.0f;
        const float _dx = 3.0f;
        
        float Img[nnz * nnx] = {1.0f, 1.0f, 1.0f,
                                1.0f, 5.0f, 1.0f,
                                1.0f, 1.0f, 1.0f};
        float laplace[nnz * nnx] = {0};
        
        cuda_laplace_filter(Img, laplace, _dz, _dx, npml, nnz, nnx);
        
        // Center element should be processed
        float expected = 4.0f*(1.0f-2*5.0f+1.0f) + 9.0f*(1.0f-2*5.0f+1.0f);
        assert(laplace[4] == expected);
        
        // Boundary elements should be 0
        for (int i = 0; i < nnz * nnx; ++i) {
            if (i != 4) {
                assert(laplace[i] == 0.0f);
            }
        }
    }
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}