// original code(id = 128): 
 /*
__global__ void expandScoreFactors ( const float * input , float * output , int dims , int clsNum ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } int k = tid / clsNum ; output [ tid ] = input [ k ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void expandScoreFactors(const float* input, float* output, int dims, int clsNum);

        int main() {
            // Test case 1: Basic functionality
            {
                const int dims = 6;
                const int clsNum = 2;
                float input[] = {1.0f, 2.0f, 3.0f};
                float output[dims];
                float expected[] = {1.0f, 1.0f, 2.0f, 2.0f, 3.0f, 3.0f};

                expandScoreFactors(input, output, dims, clsNum);

                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
                std::cout << "Test case 1 passed!" << std::endl;
            }

            // Test case 2: Single class
            {
                const int dims = 4;
                const int clsNum = 1;
                float input[] = {5.0f, 6.0f, 7.0f, 8.0f};
                float output[dims];
                float expected[] = {5.0f, 6.0f, 7.0f, 8.0f};

                expandScoreFactors(input, output, dims, clsNum);

                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
                std::cout << "Test case 2 passed!" << std::endl;
            }

            // Test case 3: Empty output
            {
                const int dims = 0;
                const int clsNum = 3;
                float input[] = {1.0f, 2.0f};
                float output[1]; // dummy array

                expandScoreFactors(input, output, dims, clsNum);
                std::cout << "Test case 3 passed!" << std::endl;
            }

            // Test case 4: Larger dimensions
            {
                const int dims = 12;
                const int clsNum = 4;
                float input[] = {10.0f, 20.0f, 30.0f};
                float output[dims];
                float expected[] = {10.0f, 10.0f, 10.0f, 10.0f,
                                    20.0f, 20.0f, 20.0f, 20.0f,
                                    30.0f, 30.0f, 30.0f, 30.0f};

                expandScoreFactors(input, output, dims, clsNum);

                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
                std::cout << "Test case 4 passed!" << std::endl;
            }

            // Test case 5: Single input element
            {
                const int dims = 5;
                const int clsNum = 5;
                float input[] = {42.0f};
                float output[dims];
                float expected[] = {42.0f, 42.0f, 42.0f, 42.0f, 42.0f};

                expandScoreFactors(input, output, dims, clsNum);

                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
                std::cout << "Test case 5 passed!" << std::endl;
            }

            return 0;
        }

        void expandScoreFactors(const float* input, float* output, int dims, int clsNum) {
            for (int tid = 0; tid < dims; ++tid) {
                int k = tid / clsNum;
                output[tid] = input[k];
            }
        }