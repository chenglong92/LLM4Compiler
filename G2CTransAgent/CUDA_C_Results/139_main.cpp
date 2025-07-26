// original code(id = 139): 
 /*
__global__ void Kernel_Softmax_seg ( float * dev_x , const int c , const int size ) { unsigned int i = blockDim . x * blockIdx . x + threadIdx . x ; int N = size ; float temp = 0. ; while ( i < N ) { for ( int j = 0 ; j < c ; j ++ ) temp = max ( dev_x [ j * size + i ] , temp ) ; for ( int j = 0 ; j < c ; j ++ ) dev_x [ j * size + i ] = expf ( dev_x [ j * size + i ] - temp ) ; temp = 0.0 ; for ( int j = 0 ; j < c ; j ++ ) temp += dev_x [ j * size + i ] ; for ( int j = 0 ; j < c ; j ++ ) dev_x [ j * size + i ] /= temp ; i += gridDim . x * blockDim . x ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <algorithm>
        #include <vector>
        #include <cassert>

        void Kernel_Softmax_seg(float* dev_x, const int c, const int size);

        int main() {
            // Test case 1: Normal case with 3 classes and 4 elements
            {
                const int c = 3;
                const int size = 4;
                std::vector<float> input = {
                    1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f
                };
                
                Kernel_Softmax_seg(input.data(), c, size);
                
                // Verify each column sums to approximately 1.0
                for (int i = 0; i < size; ++i) {
                    float sum = 0.0f;
                    for (int j = 0; j < c; ++j) {
                        sum += input[j * size + i];
                    }
                    assert(std::abs(sum - 1.0f) < 1e-6f);
                }
            }

            // Test case 2: Edge case with 1 class and 1 element
            {
                const int c = 1;
                const int size = 1;
                std::vector<float> input = {42.0f};
                
                Kernel_Softmax_seg(input.data(), c, size);
                
                assert(std::abs(input[0] - 1.0f) < 1e-6f);
            }

            // Test case 3: Edge case with 2 classes and 1 element
            {
                const int c = 2;
                const int size = 1;
                std::vector<float> input = {0.0f, 0.0f};
                
                Kernel_Softmax_seg(input.data(), c, size);
                
                float sum = input[0] + input[1];
                assert(std::abs(sum - 1.0f) < 1e-6f);
                assert(std::abs(input[0] - 0.5f) < 1e-6f);
                assert(std::abs(input[1] - 0.5f) < 1e-6f);
            }

            // Test case 4: Edge case with large values
            {
                const int c = 2;
                const int size = 3;
                std::vector<float> input = {
                    1000.0f, 1000.0f, 1000.0f,
                    1001.0f, 1001.0f, 1001.0f
                };
                
                Kernel_Softmax_seg(input.data(), c, size);
                
                for (int i = 0; i < size; ++i) {
                    float sum = input[i] + input[size + i];
                    assert(std::abs(sum - 1.0f) < 1e-6f);
                    assert(std::abs(input[i] - (1.0f / (1.0f + expf(1.0f)))) < 1e-6f);
                }
            }

            // Test case 5: Abnormal case with zero size (shouldn't crash)
            {
                const int c = 3;
                const int size = 0;
                std::vector<float> input;
                
                Kernel_Softmax_seg(input.data(), c, size);
                
                // No assertions, just checking it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }