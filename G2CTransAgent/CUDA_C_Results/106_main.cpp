// original code(id = 106): 
 /*
__global__ void nlf_down_forward ( const int n , const float * filters , const int channel , const int height , const int width , const int wsize , float * top_data ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index >= n ) { return ; } int step = height * width ; int base = index * step ; int fbase = index / channel * wsize * step ; for ( int row = 0 ; row < height ; row ++ ) { for ( int col = 0 ; col < width ; col ++ ) { float temp = 0 ; int r = row ; int c = col ; int shift = 0 * step + row * width + col ; temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; r = row - 1 ; c = col ; shift = 1 * step + row * width + col ; if ( r >= 0 ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row - 1 ; c = col - 1 ; shift = 2 * step + row * width + col ; if ( r >= 0 && c >= 0 ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row - 1 ; c = col + 1 ; shift = 3 * step + row * width + col ; if ( r >= 0 && c < width ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row ; c = col - 1 ; shift = 4 * step + row * width + col ; if ( c >= 0 ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; top_data [ base + row * width + col ] = temp ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void nlf_down_forward(const int n, const float* filters, const int channel, const int height, const int width, const int wsize, float* top_data);

int main() {
    // Test case 1: Simple 1x1 case (no neighbors)
    {
        const int n = 1;
        const int channel = 1;
        const int height = 1;
        const int width = 1;
        const int wsize = 5;
        
        float filters[wsize * height * width] = {1.0f, 0.5f, 0.25f, 0.125f, 0.0625f};
        float top_data[n * height * width] = {2.0f};
        
        nlf_down_forward(n, filters, channel, height, width, wsize, top_data);
        
        // Only the center pixel contributes (position 0)
        assert(fabs(top_data[0] - 2.0f * 1.0f) < 1e-6f);
    }
    
    // Test case 2: 2x2 case with all boundary conditions
    {
        const int n = 1;
        const int channel = 1;
        const int height = 2;
        const int width = 2;
        const int wsize = 5;
        
        float filters[wsize * height * width] = {
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // position 0 for both pixels
            0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  // position 1
            0.25f, 0.0f, 0.0f, 0.0f, 0.0f, // position 2
            0.125f, 0.0f, 0.0f, 0.0f, 0.0f,// position 3
            0.0625f, 0.0f, 0.0f, 0.0f, 0.0f // position 4
        };
        float top_data[n * height * width] = {1.0f, 2.0f, 3.0f, 4.0f};
        
        nlf_down_forward(n, filters, channel, height, width, wsize, top_data);
        
        // Pixel (0,0): only position 0,1,2,3,4 contribute (but 1,2,3,4 use current pixel due to boundaries)
        float expected00 = 1.0f * (1.0f + 0.5f + 0.25f + 0.125f + 0.0625f);
        assert(fabs(top_data[0] - expected00) < 1e-6f);
        
        // Pixel (0,1): position 0,1,3,4 contribute (position 2 is out of bounds)
        float expected01 = 2.0f * 1.0f + 2.0f * 0.5f + 2.0f * 0.125f + 1.0f * 0.0625f;
        assert(fabs(top_data[1] - expected01) < 1e-6f);
        
        // Pixel (1,0): position 0,1,2,4 contribute (position 3 is out of bounds)
        float expected10 = 3.0f * 1.0f + 1.0f * 0.5f + 1.0f * 0.25f + 3.0f * 0.0625f;
        assert(fabs(top_data[2] - expected10) < 1e-6f);
        
        // Pixel (1,1): all positions contribute with actual neighbors
        float expected11 = 4.0f * 1.0f + 2.0f * 0.5f + 1.0f * 0.25f + 3.0f * 0.125f + 3.0f * 0.0625f;
        assert(fabs(top_data[3] - expected11) < 1e-6f);
    }
    
    // Test case 3: Multiple channels and elements
    {
        const int n = 2;
        const int channel = 2;
        const int height = 2;
        const int width = 2;
        const int wsize = 5;
        
        float filters[wsize * height * width] = {
            // Element 0 (n=0, channel=0)
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            // Element 1 (n=0, channel=1)
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };
        float top_data[n * height * width] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
        
        nlf_down_forward(n, filters, channel, height, width, wsize, top_data);
        
        // First element (n=0):
        // Only position 0 contributes for channel 0
        assert(fabs(top_data[0] - 1.0f) < 1e-6f);
        assert(fabs(top_data[1] - 2.0f) < 1e-6f);
        assert(fabs(top_data[2] - 3.0f) < 1e-6f);
        assert(fabs(top_data[3] - 4.0f) < 1e-6f);
        
        // Second element (n=1):
        // Only position 1 contributes for channel 1 (using current pixel for boundaries)
        assert(fabs(top_data[4] - 5.0f * 1.0f) < 1e-6f);
        assert(fabs(top_data[5] - 6.0f * 1.0f) < 1e-6f);
        assert(fabs(top_data[6] - 7.0f * 1.0f + 5.0f * 1.0f) < 1e-6f);
        assert(fabs(top_data[7] - 8.0f * 1.0f + 6.0f * 1.0f) < 1e-6f);
    }
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

void nlf_down_forward(const int n, const float* filters, const int channel, const int height, const int width, const int wsize, float* top_data) {
    for (int index = 0; index < n; ++index) {
        int step = height * width;
        int base = index * step;
        int fbase = index / channel * wsize * step;
        
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                float temp = 0;
                int r = row;
                int c = col;
                int shift = 0 * step + row * width + col;
                temp += top_data[base + r * width + c] * filters[fbase + shift];
                
                r = row - 1;
                c = col;
                shift = 1 * step + row * width + col;
                if (r >= 0)
                    temp += top_data[base + r * width + c] * filters[fbase + shift];
                else
                    temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row - 1;
                c = col - 1;
                shift = 2 * step + row * width + col;
                if (r >= 0 && c >= 0)
                    temp += top_data[base + r * width + c] * filters[fbase + shift];
                else
                    temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row - 1;
                c = col + 1;
                shift = 3 * step + row * width + col;
                if (r >= 0 && c < width)
                    temp += top_data[base + r * width + c] * filters[fbase + shift];
                else
                    temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row;
                c = col - 1;
                shift = 4 * step + row * width + col;
                if (c >= 0)
                    temp += top_data[base + r * width + c] * filters[fbase + shift];
                else
                    temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                top_data[base + row * width + col] = temp;
            }
        }
    }
}