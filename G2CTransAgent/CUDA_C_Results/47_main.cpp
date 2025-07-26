// original code(id = 47): 
 /*
__global__ void countRangesGlobal ( int size , int * A , int * B ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i >= size ) return ; int x = A [ i ] / 100 ; B [ x ] += 1 ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void countRangesGlobal(int size, int* A, int* B);

        int main() {
            // Test case 1: Basic functionality
            {
                int A[] = {150, 250, 350, 450, 550};
                int B[10] = {0};
                int size = sizeof(A)/sizeof(A[0]);
                countRangesGlobal(size, A, B);
                assert(B[1] == 1);
                assert(B[2] == 1);
                assert(B[3] == 1);
                assert(B[4] == 1);
                assert(B[5] == 1);
            }

            // Test case 2: Empty array
            {
                int A[] = {};
                int B[10] = {0};
                int size = 0;
                countRangesGlobal(size, A, B);
                for (int i = 0; i < 10; ++i) {
                    assert(B[i] == 0);
                }
            }

            // Test case 3: Negative numbers (implementation-dependent behavior)
            {
                int A[] = {-150, -50, 50, 150};
                int B[10] = {0};
                int size = sizeof(A)/sizeof(A[0]);
                countRangesGlobal(size, A, B);
                // Note: Behavior depends on how division rounds negative numbers
                // This assumes integer division truncates towards zero
                assert(B[-1] == 1);  // -150/100 = -1
                assert(B[0] == 2);   // -50/100 = 0, 50/100 = 0
                assert(B[1] == 1);   // 150/100 = 1
            }

            // Test case 4: Large numbers and potential out-of-bounds
            {
                int A[] = {99999, 100000, 100100};
                int B[1001] = {0};  // Enough space for 100000/100 = 1000
                int size = sizeof(A)/sizeof(A[0]);
                countRangesGlobal(size, A, B);
                assert(B[999] == 1);  // 99999/100 = 999
                assert(B[1000] == 2); // 100000/100 = 1000, 100100/100 = 1001 (but array is big enough)
            }

            // Test case 5: Duplicate values mapping to same index
            {
                int A[] = {100, 100, 199, 200, 200, 200};
                int B[10] = {0};
                int size = sizeof(A)/sizeof(A[0]);
                countRangesGlobal(size, A, B);
                assert(B[1] == 3);  // 100, 100, 199
                assert(B[2] == 3);  // 200, 200, 200
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }