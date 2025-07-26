// original code(id = 214): 
 /*
__global__ void setLabels ( int * output , int dims , int clsNum ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } output [ tid ] = tid % clsNum ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void setLabels(int* output, int dims, int clsNum);

        int main() {
            // Test case 1: Normal case with dims > clsNum
            {
                const int dims = 10;
                const int clsNum = 3;
                int output[dims];
                
                setLabels(output, dims, clsNum);
                
                int expected[dims] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 2: dims is 0 (should do nothing)
            {
                const int dims = 0;
                const int clsNum = 5;
                int output[1] = {42}; // dummy value
                
                setLabels(output, dims, clsNum);
                assert(output[0] == 42); // should remain unchanged
            }

            // Test case 3: clsNum is 1 (all elements should be 0)
            {
                const int dims = 5;
                const int clsNum = 1;
                int output[dims];
                
                setLabels(output, dims, clsNum);
                
                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == 0);
                }
            }

            // Test case 4: dims exactly divisible by clsNum
            {
                const int dims = 8;
                const int clsNum = 4;
                int output[dims];
                
                setLabels(output, dims, clsNum);
                
                int expected[dims] = {0, 1, 2, 3, 0, 1, 2, 3};
                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 5: dims not divisible by clsNum
            {
                const int dims = 7;
                const int clsNum = 4;
                int output[dims];
                
                setLabels(output, dims, clsNum);
                
                int expected[dims] = {0, 1, 2, 3, 0, 1, 2};
                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == expected[i]);
                }
            }

            // Test case 6: Large values
            {
                const int dims = 1000;
                const int clsNum = 7;
                int* output = new int[dims];
                
                setLabels(output, dims, clsNum);
                
                for (int i = 0; i < dims; ++i) {
                    assert(output[i] == i % clsNum);
                }
                
                delete[] output;
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void setLabels(int* output, int dims, int clsNum) {
            for (int tid = 0; tid < dims; ++tid) {
                output[tid] = tid % clsNum;
            }
        }