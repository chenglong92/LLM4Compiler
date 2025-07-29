// original code(id = 10): 
 /*
__global__ void kernelMaximum ( float * maxhd , float * maxvd , int start , int size ) { int tx = start + threadIdx . x ; for ( int i = size >> 1 ; i > 0 ; i >>= 1 ) { __syncthreads ( ) ; if ( tx < i ) { if ( maxhd [ tx ] < maxhd [ tx + i ] ) maxhd [ tx ] = maxhd [ tx + i ] ; if ( maxvd [ tx ] < maxvd [ tx + i ] ) maxvd [ tx ] = maxvd [ tx + i ] ; } ; } ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <algorithm>
        #include <vector>

        void kernelMaximum(float* maxhd, float* maxvd, int start, int size) {
            for (int i = size >> 1; i > 0; i >>= 1) {
                for (int tx = start; tx < i; ++tx) {
                    if (maxhd[tx] < maxhd[tx + i]) {
                        maxhd[tx] = maxhd[tx + i];
                    }
                    if (maxvd[tx] < maxvd[tx + i]) {
                        maxvd[tx] = maxvd[tx + i];
                    }
                }
            }
        }

        void test_kernelMaximum() {
            // Test case 1: Small arrays with size 2
            {
                float maxhd[] = {1.0f, 2.0f};
                float maxvd[] = {3.0f, 4.0f};
                int start = 0;
                int size = 2;
                kernelMaximum(maxhd, maxvd, start, size);
                assert(maxhd[0] == 2.0f);
                assert(maxvd[0] == 4.0f);
            }

            // Test case 2: Larger arrays with size 8
            {
                float maxhd[] = {1.0f, 3.0f, 5.0f, 7.0f, 2.0f, 4.0f, 6.0f, 8.0f};
                float maxvd[] = {8.0f, 6.0f, 4.0f, 2.0f, 7.0f, 5.0f, 3.0f, 1.0f};
                int start = 0;
                int size = 8;
                kernelMaximum(maxhd, maxvd, start, size);
                assert(maxhd[0] == 8.0f);
                assert(maxvd[0] == 8.0f);
            }

            // Test case 3: Non-zero start index
            {
                float maxhd[] = {1.0f, 3.0f, 5.0f, 7.0f, 2.0f, 4.0f, 6.0f, 8.0f};
                float maxvd[] = {8.0f, 6.0f, 4.0f, 2.0f, 7.0f, 5.0f, 3.0f, 1.0f};
                int start = 2;
                int size = 8;
                kernelMaximum(maxhd, maxvd, start, size);
                // Only elements from index 2 are processed
                assert(maxhd[2] == 8.0f);
                assert(maxvd[2] == 8.0f);
            }

            // Test case 4: Arrays with all equal elements
            {
                float maxhd[] = {5.0f, 5.0f, 5.0f, 5.0f};
                float maxvd[] = {5.0f, 5.0f, 5.0f, 5.0f};
                int start = 0;
                int size = 4;
                kernelMaximum(maxhd, maxvd, start, size);
                assert(maxhd[0] == 5.0f);
                assert(maxvd[0] == 5.0f);
            }

            // Test case 5: Single element array (should do nothing)
            {
                float maxhd[] = {1.0f};
                float maxvd[] = {2.0f};
                int start = 0;
                int size = 1;
                kernelMaximum(maxhd, maxvd, start, size);
                assert(maxhd[0] == 1.0f);
                assert(maxvd[0] == 2.0f);
            }
        }

        int main() {
            test_kernelMaximum();
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }