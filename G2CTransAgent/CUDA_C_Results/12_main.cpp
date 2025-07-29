// original code(id = 12): 
 /*
__global__ void testInt1 ( const int * input , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } int sum ; for ( int i = 0 ; i < 3000 * 4 ; i ++ ) { if ( input [ i ] == 0 ) { sum ++ ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void testInt1(const int* input, int dims);

        int main() {
            // Test case 1: All zeros
            {
                const int size = 3000 * 4;
                int input[size];
                for (int i = 0; i < size; ++i) {
                    input[i] = 0;
                }
                testInt1(input, 5);
                std::cout << "Test case 1 passed: All zeros" << std::endl;
            }

            // Test case 2: No zeros
            {
                const int size = 3000 * 4;
                int input[size];
                for (int i = 0; i < size; ++i) {
                    input[i] = 1;
                }
                testInt1(input, 3);
                std::cout << "Test case 2 passed: No zeros" << std::endl;
            }

            // Test case 3: Mixed zeros and non-zeros
            {
                const int size = 3000 * 4;
                int input[size];
                for (int i = 0; i < size; ++i) {
                    input[i] = (i % 2 == 0) ? 0 : 1;
                }
                testInt1(input, 2);
                std::cout << "Test case 3 passed: Mixed zeros and non-zeros" << std::endl;
            }

            // Test case 4: Single iteration (dims = 1)
            {
                const int size = 3000 * 4;
                int input[size];
                for (int i = 0; i < size; ++i) {
                    input[i] = (i % 3 == 0) ? 0 : 1;
                }
                testInt1(input, 1);
                std::cout << "Test case 4 passed: Single iteration" << std::endl;
            }

            // Test case 5: Empty iteration (dims = 0)
            {
                const int size = 3000 * 4;
                int input[size];
                for (int i = 0; i < size; ++i) {
                    input[i] = i;
                }
                testInt1(input, 0);
                std::cout << "Test case 5 passed: Empty iteration" << std::endl;
            }

            return 0;
        }

        void testInt1(const int* input, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                int sum = 0;
                for (int i = 0; i < 3000 * 4; ++i) {
                    if (input[i] == 0) {
                        sum++;
                    }
                }
                // sum is unused in original code
            }
        }