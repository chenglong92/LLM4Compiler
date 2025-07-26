// original code(id = 231): 
 /*
__global__ void dual_ascent ( float * xn , float * xbar , float * y1 , float * y2 , float * img , float tau , float lambda , float theta , int w , int h , int nc ) { int x = threadIdx . x + blockDim . x * blockIdx . x ; int y = threadIdx . y + blockDim . y * blockIdx . y ; if ( x < w && y < h ) { int i ; float d1 , d2 , val ; for ( int z = 0 ; z < nc ; z ++ ) { i = x + w * y + w * h * z ; d1 = ( x + 1 < w ? y1 [ i ] : 0.f ) - ( x > 0 ? y1 [ ( x - 1 ) + w * y + w * h * z ] : 0.f ) ; d2 = ( y + 1 < h ? y2 [ i ] : 0.f ) - ( y > 0 ? y2 [ x + w * ( y - 1 ) + w * h * z ] : 0.f ) ; val = xn [ i ] ; xn [ i ] = ( ( val + tau * ( d1 + d2 ) ) + tau * lambda * img [ i ] ) / ( 1.f + tau * lambda ) ; xbar [ i ] = xn [ i ] + theta * ( xn [ i ] - val ) ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void dual_ascent(float* xn, float* xbar, float* y1, float* y2, float* img, float tau, float lambda, float theta, int w, int h, int nc);

int main() {
    // Test case 1: Normal case with small dimensions
    {
        int w = 3, h = 3, nc = 1;
        float tau = 0.1f, lambda = 0.5f, theta = 1.0f;
        
        float xn[9] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f};
        float xbar[9] = {0};
        float y1[9] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
        float y2[9] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
        float img[9] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
        
        dual_ascent(xn, xbar, y1, y2, img, tau, lambda, theta, w, h, nc);
        
        // Verify some values changed
        assert(xn[0] != 0.1f);
        assert(xbar[0] != 0.0f);
    }

    // Test case 2: Edge case with minimum dimensions
    {
        int w = 1, h = 1, nc = 1;
        float tau = 0.1f, lambda = 0.5f, theta = 1.0f;
        
        float xn[1] = {0.5f};
        float xbar[1] = {0};
        float y1[1] = {0.1f};
        float y2[1] = {0.1f};
        float img[1] = {0.5f};
        
        dual_ascent(xn, xbar, y1, y2, img, tau, lambda, theta, w, h, nc);
        
        // Verify calculations
        float expected_xn = (0.5f + tau * (0.f + 0.f) + tau * lambda * 0.5f) / (1.f + tau * lambda);
        assert(std::abs(xn[0] - expected_xn) < 1e-6f);
        assert(std::abs(xbar[0] - (xn[0] + theta * (xn[0] - 0.5f))) < 1e-6f);
    }

    // Test case 3: Multiple color channels
    {
        int w = 2, h = 2, nc = 3;
        float tau = 0.1f, lambda = 0.5f, theta = 1.0f;
        
        float xn[12] = {0};
        float xbar[12] = {0};
        float y1[12] = {0.1f};
        float y2[12] = {0.1f};
        float img[12] = {0.5f};
        
        // Set different values for each channel
        for (int i = 0; i < 12; ++i) {
            xn[i] = 0.1f * (i % 3 + 1);
            y1[i] = 0.1f * (i % 3 + 1);
            y2[i] = 0.1f * (i % 3 + 1);
            img[i] = 0.5f * (i % 3 + 1);
        }
        
        dual_ascent(xn, xbar, y1, y2, img, tau, lambda, theta, w, h, nc);
        
        // Verify all channels were processed
        for (int i = 0; i < 12; ++i) {
            assert(xn[i] != 0.0f);
            assert(xbar[i] != 0.0f);
        }
    }

    // Test case 4: Boundary conditions
    {
        int w = 2, h = 2, nc = 1;
        float tau = 0.1f, lambda = 0.5f, theta = 1.0f;
        
        float xn[4] = {0.1f, 0.2f, 0.3f, 0.4f};
        float xbar[4] = {0};
        float y1[4] = {0.1f, 0.2f, 0.3f, 0.4f};
        float y2[4] = {0.1f, 0.2f, 0.3f, 0.4f};
        float img[4] = {0.5f, 0.5f, 0.5f, 0.5f};
        
        dual_ascent(xn, xbar, y1, y2, img, tau, lambda, theta, w, h, nc);
        
        // Verify boundary handling (rightmost and bottom elements)
        float d1_right = (0.f - y1[0]);
        float d2_bottom = (0.f - y2[2]);
        float expected_xn_right = (0.2f + tau * (d1_right + (y2[3] - y2[1])) + tau * lambda * 0.5f) / (1.f + tau * lambda);
        float expected_xn_bottom = (0.3f + tau * ((y1[3] - y1[2]) + d2_bottom) + tau * lambda * 0.5f) / (1.f + tau * lambda);
        
        assert(std::abs(xn[1] - expected_xn_right) < 1e-6f);
        assert(std::abs(xn[2] - expected_xn_bottom) < 1e-6f);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void dual_ascent(float* xn, float* xbar, float* y1, float* y2, float* img, float tau, float lambda, float theta, int w, int h, int nc) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            for (int z = 0; z < nc; ++z) {
                int i = x + w * y + w * h * z;
                float d1 = (x + 1 < w ? y1[i] : 0.f) - (x > 0 ? y1[(x - 1) + w * y + w * h * z] : 0.f);
                float d2 = (y + 1 < h ? y2[i] : 0.f) - (y > 0 ? y2[x + w * (y - 1) + w * h * z] : 0.f);
                float val = xn[i];
                xn[i] = ((val + tau * (d1 + d2)) + tau * lambda * img[i]) / (1.f + tau * lambda);
                xbar[i] = xn[i] + theta * (xn[i] - val);
            }
        }
    }
}