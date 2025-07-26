// original code(id = 121): 
 /*
__global__ void pad_input ( float * f_in , float * f_out , int H , int W , int D , int pad ) { int col = blockIdx . x * blockDim . x + threadIdx . x ; int row = blockIdx . y * blockDim . y + threadIdx . y ; int dep = blockIdx . z * blockDim . z + threadIdx . z ; int new_H = H + 2 * pad ; int new_W = W + 2 * pad ; int i = dep * new_H * new_W + col * new_W + row ; int j = dep * H * W + ( col - pad ) * W + ( row - pad ) ; if ( col < new_H && row < new_W && dep < D ) { if ( ( col < pad || col > H + pad - 1 ) || ( row < pad || row > W + pad - 1 ) ) f_out [ i ] = 0 ; else f_out [ i ] = f_in [ j ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void pad_input(float* f_in, float* f_out, int H, int W, int D, int pad);

        int main() {
            // Test case 1: Small 2x2x1 array with padding 1
            {
                const int H = 2, W = 2, D = 1, pad = 1;
                float input[H * W * D] = {1, 2, 3, 4};
                const int new_H = H + 2 * pad;
                const int new_W = W + 2 * pad;
                float output[new_H * new_W * D] = {0};
                
                pad_input(input, output, H, W, D, pad);
                
                // Expected output (4x4x1):
                // 0 0 0 0
                // 0 1 2 0
                // 0 3 4 0
                // 0 0 0 0
                float expected[new_H * new_W * D] = {
                    0, 0, 0, 0,
                    0, 1, 2, 0,
                    0, 3, 4, 0,
                    0, 0, 0, 0
                };
                
                assert(memcmp(output, expected, sizeof(expected)) == 0);
            }

            // Test case 2: 3x3x2 array with padding 2
            {
                const int H = 3, W = 3, D = 2, pad = 2;
                float input[H * W * D] = {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
                    10, 11, 12,
                    13, 14, 15,
                    16, 17, 18
                };
                const int new_H = H + 2 * pad;
                const int new_W = W + 2 * pad;
                float output[new_H * new_W * D] = {0};
                
                pad_input(input, output, H, W, D, pad);
                
                // Check padding is correct
                for (int d = 0; d < D; ++d) {
                    for (int h = 0; h < new_H; ++h) {
                        for (int w = 0; w < new_W; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            if (h < pad || h >= H + pad || w < pad || w >= W + pad) {
                                assert(output[idx] == 0);
                            }
                        }
                    }
                }
                
                // Check original content is preserved
                for (int d = 0; d < D; ++d) {
                    for (int h = 0; h < H; ++h) {
                        for (int w = 0; w < W; ++w) {
                            int input_idx = d * H * W + h * W + w;
                            int output_idx = d * new_H * new_W + (h + pad) * new_W + (w + pad);
                            assert(output[output_idx] == input[input_idx]);
                        }
                    }
                }
            }

            // Test case 3: 1x1x1 array with padding 0 (no padding)
            {
                const int H = 1, W = 1, D = 1, pad = 0;
                float input[H * W * D] = {42};
                const int new_H = H + 2 * pad;
                const int new_W = W + 2 * pad;
                float output[new_H * new_W * D] = {0};
                
                pad_input(input, output, H, W, D, pad);
                
                assert(output[0] == input[0]);
            }

            // Test case 4: 4x1x3 array with padding 1
            {
                const int H = 4, W = 1, D = 3, pad = 1;
                float input[H * W * D] = {
                    1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12
                };
                const int new_H = H + 2 * pad;
                const int new_W = W + 2 * pad;
                float output[new_H * new_W * D] = {0};
                
                pad_input(input, output, H, W, D, pad);
                
                // Check padding is correct
                for (int d = 0; d < D; ++d) {
                    for (int h = 0; h < new_H; ++h) {
                        for (int w = 0; w < new_W; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            if (h < pad || h >= H + pad || w < pad || w >= W + pad) {
                                assert(output[idx] == 0);
                            }
                        }
                    }
                }
                
                // Check original content is preserved
                for (int d = 0; d < D; ++d) {
                    for (int h = 0; h < H; ++h) {
                        for (int w = 0; w < W; ++w) {
                            int input_idx = d * H * W + h * W + w;
                            int output_idx = d * new_H * new_W + (h + pad) * new_W + (w + pad);
                            assert(output[output_idx] == input[input_idx]);
                        }
                    }
                }
            }

            // Test case 5: 2x3x2 array with large padding (3)
            {
                const int H = 2, W = 3, D = 2, pad = 3;
                float input[H * W * D] = {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
                    10, 11, 12
                };
                const int new_H = H + 2 * pad;
                const int new_W = W + 2 * pad;
                float output[new_H * new_W * D] = {0};
                
                pad_input(input, output, H, W, D, pad);
                
                // Check the center region contains original data
                for (int d = 0; d < D; ++d) {
                    for (int h = pad; h < H + pad; ++h) {
                        for (int w = pad; w < W + pad; ++w) {
                            int input_idx = d * H * W + (h - pad) * W + (w - pad);
                            int output_idx = d * new_H * new_W + h * new_W + w;
                            assert(output[output_idx] == input[input_idx]);
                        }
                    }
                }
                
                // Check all padding is zero
                for (int d = 0; d < D; ++d) {
                    // Top and bottom padding
                    for (int h = 0; h < pad; ++h) {
                        for (int w = 0; w < new_W; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            assert(output[idx] == 0);
                        }
                    }
                    for (int h = H + pad; h < new_H; ++h) {
                        for (int w = 0; w < new_W; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            assert(output[idx] == 0);
                        }
                    }
                    
                    // Left and right padding (only for rows that aren't fully padded)
                    for (int h = pad; h < H + pad; ++h) {
                        for (int w = 0; w < pad; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            assert(output[idx] == 0);
                        }
                        for (int w = W + pad; w < new_W; ++w) {
                            int idx = d * new_H * new_W + h * new_W + w;
                            assert(output[idx] == 0);
                        }
                    }
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void pad_input(float* f_in, float* f_out, int H, int W, int D, int pad) {
            int new_H = H + 2 * pad;
            int new_W = W + 2 * pad;
            
            for (int dep = 0; dep < D; ++dep) {
                for (int col = 0; col < new_H; ++col) {
                    for (int row = 0; row < new_W; ++row) {
                        int i = dep * new_H * new_W + col * new_W + row;
                        if ((col < pad || col > H + pad - 1) || (row < pad || row > W + pad - 1)) {
                            f_out[i] = 0;
                        } else {
                            int j = dep * H * W + (col - pad) * W + (row - pad);
                            f_out[i] = f_in[j];
                        }
                    }
                }
            }
        }