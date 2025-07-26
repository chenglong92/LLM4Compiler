// original code(id = 94): 
 /*
__global__ void nlf_up_forward ( const int n , const float * filters , const int channel , const int height , const int width , const int wsize , float * top_data ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index >= n ) { return ; } int step = height * width ; int base = index * step ; int fbase = index / channel * wsize * step ; for ( int row = height - 1 ; row >= 0 ; row -- ) { for ( int col = width - 1 ; col >= 0 ; col -- ) { float temp = 0 ; int r = row ; int c = col ; int shift = 0 * step + row * width + col ; temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; r = row + 1 ; c = col ; shift = 1 * step + row * width + col ; if ( r < height ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row + 1 ; c = col - 1 ; shift = 2 * step + row * width + col ; if ( r < height && c >= 0 ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row + 1 ; c = col + 1 ; shift = 3 * step + row * width + col ; if ( r < height && c < width ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; r = row ; c = col + 1 ; shift = 4 * step + row * width + col ; if ( c < width ) temp += top_data [ base + r * width + c ] * filters [ fbase + shift ] ; else temp += top_data [ base + row * width + col ] * filters [ fbase + shift ] ; top_data [ base + row * width + col ] = temp ; } } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cmath>

void nlf_up_forward(const int n, const float* filters, const int channel, const int height, const int width, const int wsize, float* top_data);

int main() {
    // Test case 1: Basic 2x2 single channel case
    {
        const int n = 1;
        const int channel = 1;
        const int height = 2;
        const int width = 2;
        const int wsize = 5;
        
        float filters[n * wsize * height * width] = {
            1.0f, 0.5f, 0.5f, 0.5f, 0.5f,
            0.5f, 1.0f, 0.5f, 0.5f, 0.5f
        };
        
        float top_data[n * height * width] = {
            1.0f, 2.0f,
            3.0f, 4.0f
        };
        
        float expected[n * height * width] = {
            1.0f*1.0f + 3.0f*0.5f + 3.0f*0.5f + 3.0f*0.5f + 2.0f*0.5f,
            2.0f*0.5f + 4.0f*1.0f + 4.0f*0.5f + 4.0f*0.5f + 2.0f*0.5f,
            3.0f*1.0f + 3.0f*0.5f + 3.0f*0.5f + 3.0f*0.5f + 4.0f*0.5f,
            4.0f*0.5f + 4.0f*1.0f + 4.0f*0.5f + 4.0f*0.5f + 4.0f*0.5f
        };
        
        nlf_up_forward(n, filters, channel, height, width, wsize, top_data);
        
        for (int i = 0; i < n * height * width; ++i) {
            assert(fabs(top_data[i] - expected[i]) < 1e-5f);
        }
    }
    
    // Test case 2: 3x2 multi-channel case testing boundaries
    {
        const int n = 2;
        const int channel = 2;
        const int height = 3;
        const int width = 2;
        const int wsize = 5;
        
        float filters[n * wsize * height * width] = {
            // Channel 1 filters
            1.0f, 0.1f, 0.2f, 0.3f, 0.4f,
            0.5f, 1.0f, 0.6f, 0.7f, 0.8f,
            0.9f, 1.0f, 1.1f, 1.2f, 1.3f,
            // Channel 2 filters
            2.0f, 0.2f, 0.4f, 0.6f, 0.8f,
            1.0f, 2.0f, 1.2f, 1.4f, 1.6f,
            1.8f, 2.0f, 2.2f, 2.4f, 2.6f
        };
        
        float top_data[n * height * width] = {
            1.0f, 2.0f,
            3.0f, 4.0f,
            5.0f, 6.0f,
            
            7.0f, 8.0f,
            9.0f, 10.0f,
            11.0f, 12.0f
        };
        
        nlf_up_forward(n, filters, channel, height, width, wsize, top_data);
        
        // Verify some key positions
        // First channel, top-left corner (should use boundary conditions)
        float tl = top_data[0];
        float expected_tl = 1.0f*1.0f + 3.0f*0.5f + 3.0f*0.9f + 3.0f*0.5f + 2.0f*0.5f;
        assert(fabs(tl - expected_tl) < 1e-5f);
        
        // First channel, bottom-right corner
        float br = top_data[5];
        float expected_br = 6.0f*0.8f + 6.0f*1.6f + 6.0f*2.6f + 6.0f*1.6f + 6.0f*1.6f;
        assert(fabs(br - expected_br) < 1e-5f);
        
        // Second channel, middle position
        float mid = top_data[7];
        float expected_mid = 10.0f*1.0f + 12.0f*1.8f + 12.0f*1.0f + 12.0f*1.0f + 10.0f*1.0f;
        assert(fabs(mid - expected_mid) < 1e-5f);
    }
    
    // Test case 3: 1x3 single channel case (edge cases)
    {
        const int n = 1;
        const int channel = 1;
        const int height = 1;
        const int width = 3;
        const int wsize = 5;
        
        float filters[n * wsize * height * width] = {
            1.0f, 0.5f, 0.5f, 0.5f, 0.5f
        };
        
        float top_data[n * height * width] = {1.0f, 2.0f, 3.0f};
        
        nlf_up_forward(n, filters, channel, height, width, wsize, top_data);
        
        // All positions should use boundary conditions
        assert(fabs(top_data[0] - (1.0f*1.0f + 1.0f*0.5f + 1.0f*0.5f + 1.0f*0.5f + 2.0f*0.5f)) < 1e-5f);
        assert(fabs(top_data[1] - (2.0f*1.0f + 2.0f*0.5f + 2.0f*0.5f + 2.0f*0.5f + 3.0f*0.5f)) < 1e-5f);
        assert(fabs(top_data[2] - (3.0f*1.0f + 3.0f*0.5f + 3.0f*0.5f + 3.0f*0.5f + 3.0f*0.5f)) < 1e-5f);
    }
    
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

void nlf_up_forward(const int n, const float* filters, const int channel, const int height, const int width, const int wsize, float* top_data) {
    for (int index = 0; index < n; ++index) {
        int step = height * width;
        int base = index * step;
        int fbase = index / channel * wsize * step;
        
        for (int row = height - 1; row >= 0; --row) {
            for (int col = width - 1; col >= 0; --col) {
                float temp = 0;
                int r = row;
                int c = col;
                int shift = 0 * step + row * width + col;
                temp += top_data[base + r * width + c] * filters[fbase + shift];
                
                r = row + 1;
                c = col;
                shift = 1 * step + row * width + col;
                if (r < height) temp += top_data[base + r * width + c] * filters[fbase + shift];
                else temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row + 1;
                c = col - 1;
                shift = 2 * step + row * width + col;
                if (r < height && c >= 0) temp += top_data[base + r * width + c] * filters[fbase + shift];
                else temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row + 1;
                c = col + 1;
                shift = 3 * step + row * width + col;
                if (r < height && c < width) temp += top_data[base + r * width + c] * filters[fbase + shift];
                else temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                r = row;
                c = col + 1;
                shift = 4 * step + row * width + col;
                if (c < width) temp += top_data[base + r * width + c] * filters[fbase + shift];
                else temp += top_data[base + row * width + col] * filters[fbase + shift];
                
                top_data[base + row * width + col] = temp;
            }
        }
    }
}