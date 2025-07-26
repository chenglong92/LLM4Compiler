// original code(id = 190): 
 /*
__global__ void conv1x1 ( int input_channels , int input_size , int n , float * input_im , float * filter_weight , float * filter_bias , float * output_im ) { int filter_index = blockIdx . x * blockDim . x + threadIdx . x ; if ( filter_index < n ) { filter_weight += filter_index * input_channels ; float bias = filter_bias [ filter_index ] ; output_im += filter_index * input_size * input_size ; for ( int i = 0 ; i < input_size ; i ++ ) { for ( int j = 0 ; j < input_size ; j ++ ) { float tmp = bias ; for ( int k = 0 ; k < input_channels ; k ++ ) { tmp += input_im [ k * input_size * input_size + i * input_size + j ] * filter_weight [ k ] ; } output_im [ i * input_size + j ] = ( tmp > 0.0 ) ? tmp : 0.0 ; } } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void conv1x1(int input_channels, int input_size, int n, float* input_im, float* filter_weight, float* filter_bias, float* output_im) {
            for (int filter_index = 0; filter_index < n; ++filter_index) {
                float* current_filter_weight = filter_weight + filter_index * input_channels;
                float bias = filter_bias[filter_index];
                float* current_output_im = output_im + filter_index * input_size * input_size;
                
                for (int i = 0; i < input_size; ++i) {
                    for (int j = 0; j < input_size; ++j) {
                        float tmp = bias;
                        for (int k = 0; k < input_channels; ++k) {
                            tmp += input_im[k * input_size * input_size + i * input_size + j] * current_filter_weight[k];
                        }
                        current_output_im[i * input_size + j] = (tmp > 0.0f) ? tmp : 0.0f;
                    }
                }
            }
        }

        void test_conv1x1() {
            // Test case 1: Basic test with small inputs
            {
                const int input_channels = 1;
                const int input_size = 2;
                const int n = 1;
                float input_im[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float filter_weight[] = {0.5f};
                float filter_bias[] = {1.0f};
                float output_im[4] = {0};
                float expected_output[] = {1.5f, 2.0f, 2.5f, 3.0f};
                
                conv1x1(input_channels, input_size, n, input_im, filter_weight, filter_bias, output_im);
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(output_im[i] - expected_output[i]) < 1e-6f);
                }
            }
            
            // Test case 2: Multiple input channels
            {
                const int input_channels = 2;
                const int input_size = 2;
                const int n = 1;
                float input_im[] = {1.0f, 2.0f, 3.0f, 4.0f,  // Channel 1
                                    0.5f, 1.0f, 1.5f, 2.0f}; // Channel 2
                float filter_weight[] = {0.5f, -0.25f};
                float filter_bias[] = {0.1f};
                float output_im[4] = {0};
                float expected_output[] = {0.1f + 1.0f*0.5f + 0.5f*(-0.25f),
                                          0.1f + 2.0f*0.5f + 1.0f*(-0.25f),
                                          0.1f + 3.0f*0.5f + 1.5f*(-0.25f),
                                          0.1f + 4.0f*0.5f + 2.0f*(-0.25f)};
                
                conv1x1(input_channels, input_size, n, input_im, filter_weight, filter_bias, output_im);
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(output_im[i] - expected_output[i]) < 1e-6f);
                }
            }
            
            // Test case 3: Multiple filters
            {
                const int input_channels = 1;
                const int input_size = 2;
                const int n = 2;
                float input_im[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float filter_weight[] = {0.5f, -0.25f};
                float filter_bias[] = {1.0f, -0.5f};
                float output_im[8] = {0};
                float expected_output[] = {1.5f, 2.0f, 2.5f, 3.0f,  // Filter 1
                                          -0.75f, -1.0f, -1.25f, -1.5f}; // Filter 2
                
                conv1x1(input_channels, input_size, n, input_im, filter_weight, filter_bias, output_im);
                
                for (int i = 0; i < 8; ++i) {
                    assert(fabs(output_im[i] - expected_output[i]) < 1e-6f);
                }
            }
            
            // Test case 4: ReLU activation (negative values become 0)
            {
                const int input_channels = 1;
                const int input_size = 2;
                const int n = 1;
                float input_im[] = {-1.0f, -2.0f, -3.0f, -4.0f};
                float filter_weight[] = {0.5f};
                float filter_bias[] = {-1.0f};
                float output_im[4] = {0};
                float expected_output[] = {0.0f, 0.0f, 0.0f, 0.0f};
                
                conv1x1(input_channels, input_size, n, input_im, filter_weight, filter_bias, output_im);
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(output_im[i] - expected_output[i]) < 1e-6f);
                }
            }
            
            // Test case 5: Edge case with single pixel input
            {
                const int input_channels = 3;
                const int input_size = 1;
                const int n = 2;
                float input_im[] = {0.1f, 0.2f, 0.3f};
                float filter_weight[] = {1.0f, 0.0f, -1.0f,  // Filter 1
                                        0.5f, 0.5f, 0.5f};   // Filter 2
                float filter_bias[] = {0.1f, -0.1f};
                float output_im[2] = {0};
                float expected_output[] = {0.1f + 0.1f*1.0f + 0.2f*0.0f + 0.3f*(-1.0f),
                                          -0.1f + 0.1f*0.5f + 0.2f*0.5f + 0.3f*0.5f};
                
                conv1x1(input_channels, input_size, n, input_im, filter_weight, filter_bias, output_im);
                
                for (int i = 0; i < 2; ++i) {
                    assert(fabs(output_im[i] - expected_output[i]) < 1e-6f);
                }
            }
        }

        int main() {
            test_conv1x1();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }