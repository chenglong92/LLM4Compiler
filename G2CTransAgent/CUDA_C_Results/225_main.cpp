// original code(id = 225): 
 /*
__global__ void histogram ( int n , int * color , int * bucket ) { int i = threadIdx . x + blockDim . x * blockIdx . x ; if ( i < n ) { int c = color [ i ] ; bucket [ c ] += 1 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void histogram(int n, int* color, int* bucket);

        int main() {
            // Test case 1: Basic test with a small array
            {
                int color[] = {0, 1, 2, 3, 0, 1, 2, 3};
                int bucket[4] = {0};
                int expected[] = {2, 2, 2, 2};
                histogram(8, color, bucket);
                for (int i = 0; i < 4; ++i) {
                    assert(bucket[i] == expected[i]);
                }
            }

            // Test case 2: All elements have the same color
            {
                int color[] = {1, 1, 1, 1, 1};
                int bucket[2] = {0};
                int expected[] = {0, 5};
                histogram(5, color, bucket);
                for (int i = 0; i < 2; ++i) {
                    assert(bucket[i] == expected[i]);
                }
            }

            // Test case 3: Empty array
            {
                int color[] = {};
                int bucket[3] = {0};
                int expected[] = {0, 0, 0};
                histogram(0, color, bucket);
                for (int i = 0; i < 3; ++i) {
                    assert(bucket[i] == expected[i]);
                }
            }

            // Test case 4: Single element
            {
                int color[] = {2};
                int bucket[3] = {0};
                int expected[] = {0, 0, 1};
                histogram(1, color, bucket);
                for (int i = 0; i < 3; ++i) {
                    assert(bucket[i] == expected[i]);
                }
            }

            // Test case 5: Large array with multiple colors
            {
                const int size = 1000;
                int color[size];
                for (int i = 0; i < size; ++i) {
                    color[i] = i % 10;
                }
                int bucket[10] = {0};
                int expected[10];
                for (int i = 0; i < 10; ++i) {
                    expected[i] = size / 10;
                }
                histogram(size, color, bucket);
                for (int i = 0; i < 10; ++i) {
                    assert(bucket[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void histogram(int n, int* color, int* bucket) {
            for (int i = 0; i < n; ++i) {
                int c = color[i];
                bucket[c] += 1;
            }
        }