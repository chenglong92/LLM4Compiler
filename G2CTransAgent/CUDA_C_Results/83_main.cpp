// original code(id = 83): 
 /*
__global__ void convertEdgeMaskToFloatDevice ( float * d_output , unsigned char * d_input , unsigned int width , unsigned int height ) { const int x = blockIdx . x * blockDim . x + threadIdx . x ; const int y = blockIdx . y * blockDim . y + threadIdx . y ; if ( x >= width || y >= height ) return ; d_output [ y * width + x ] = min ( d_input [ y * width + x ] , d_input [ width * height + y * width + x ] ) ; }
*/
// optimized code: 

#include <iostream>
        #include <algorithm>
        #include <cassert>
        #include <vector>
        #include <random>

        void convertEdgeMaskToFloat(float* d_output, unsigned char* d_input, unsigned int width, unsigned int height) {
            for (unsigned int y = 0; y < height; ++y) {
                for (unsigned int x = 0; x < width; ++x) {
                    d_output[y * width + x] = std::min(
                        static_cast<float>(d_input[y * width + x]),
                        static_cast<float>(d_input[width * height + y * width + x])
                    );
                }
            }
        }

        void testConvertEdgeMaskToFloat() {
            // Test case 1: Small 2x2 array
            {
                const unsigned int width = 2;
                const unsigned int height = 2;
                unsigned char input[8] = {10, 20, 30, 40, 5, 15, 25, 35};
                float output[4] = {0};
                float expected[4] = {5, 15, 25, 35};
                
                convertEdgeMaskToFloat(output, input, width, height);
                
                for (unsigned int i = 0; i < width * height; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 2: Single element array
            {
                const unsigned int width = 1;
                const unsigned int height = 1;
                unsigned char input[2] = {100, 50};
                float output[1] = {0};
                float expected[1] = {50};
                
                convertEdgeMaskToFloat(output, input, width, height);
                
                assert(output[0] == expected[0]);
            }

            // Test case 3: Rectangular array (3x2)
            {
                const unsigned int width = 3;
                const unsigned int height = 2;
                unsigned char input[12] = {10, 20, 30, 40, 50, 60, 5, 15, 25, 35, 45, 55};
                float output[6] = {0};
                float expected[6] = {5, 15, 25, 35, 45, 55};
                
                convertEdgeMaskToFloat(output, input, width, height);
                
                for (unsigned int i = 0; i < width * height; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 4: All zeros
            {
                const unsigned int width = 2;
                const unsigned int height = 2;
                unsigned char input[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                float output[4] = {0};
                float expected[4] = {0, 0, 0, 0};
                
                convertEdgeMaskToFloat(output, input, width, height);
                
                for (unsigned int i = 0; i < width * height; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 5: Random large array
            {
                const unsigned int width = 100;
                const unsigned int height = 100;
                std::vector<unsigned char> input(width * height * 2);
                std::vector<float> output(width * height);
                std::vector<float> expected(width * height);
                
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<unsigned char> dis(0, 255);
                
                for (unsigned int i = 0; i < width * height * 2; ++i) {
                    input[i] = dis(gen);
                }
                
                for (unsigned int y = 0; y < height; ++y) {
                    for (unsigned int x = 0; x < width; ++x) {
                        expected[y * width + x] = std::min(
                            static_cast<float>(input[y * width + x]),
                            static_cast<float>(input[width * height + y * width + x])
                        );
                    }
                }
                
                convertEdgeMaskToFloat(output.data(), input.data(), width, height);
                
                for (unsigned int i = 0; i < width * height; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 6: First half is smaller
            {
                const unsigned int width = 2;
                const unsigned int height = 2;
                unsigned char input[8] = {5, 15, 25, 35, 10, 20, 30, 40};
                float output[4] = {0};
                float expected[4] = {5, 15, 25, 35};
                
                convertEdgeMaskToFloat(output, input, width, height);
                
                for (unsigned int i = 0; i < width * height; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            std::cout << "All tests passed successfully!" << std::endl;
        }

        int main() {
            testConvertEdgeMaskToFloat();
            return 0;
        }