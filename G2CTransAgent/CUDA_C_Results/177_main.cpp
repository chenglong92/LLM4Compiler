// original code(id = 177): 
 /*
__global__ void sum_array_overlap ( int * a , int * b , int * c , int N ) { int gid = blockIdx . x * blockDim . x + threadIdx . x ; if ( gid < N ) { c [ gid ] = a [ gid ] + b [ gid ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <climits>
        #include <cassert>

        void sum_array_overlap(int* a, int* b, int* c, int N);

        int main() {
            // Test case 1: Normal case with positive numbers
            {
                int a[] = {1, 2, 3, 4, 5};
                int b[] = {10, 20, 30, 40, 50};
                int c[5];
                int expected[] = {11, 22, 33, 44, 55};
                sum_array_overlap(a, b, c, 5);
                for (int i = 0; i < 5; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 2: Case with negative numbers
            {
                int a[] = {-1, -2, -3, -4, -5};
                int b[] = {-10, -20, -30, -40, -50};
                int c[5];
                int expected[] = {-11, -22, -33, -44, -55};
                sum_array_overlap(a, b, c, 5);
                for (int i = 0; i < 5; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 3: Mixed positive and negative numbers
            {
                int a[] = {-1, 2, -3, 4, -5};
                int b[] = {10, -20, 30, -40, 50};
                int c[5];
                int expected[] = {9, -18, 27, -36, 45};
                sum_array_overlap(a, b, c, 5);
                for (int i = 0; i < 5; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 4: Edge case with N=0
            {
                int a[] = {1, 2, 3};
                int b[] = {4, 5, 6};
                int c[] = {0, 0, 0};
                int original_c[] = {0, 0, 0};
                sum_array_overlap(a, b, c, 0);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == original_c[i]);
                }
            }

            // Test case 5: Maximum/minimum integer values
            {
                int a[] = {INT_MAX, INT_MIN, INT_MAX};
                int b[] = {1, 1, -1};
                int c[3];
                sum_array_overlap(a, b, c, 3);
                assert(c[0] == INT_MIN); // INT_MAX + 1 overflows to INT_MIN
                assert(c[1] == INT_MIN + 1);
                assert(c[2] == INT_MAX - 1);
            }

            // Test case 6: Identical input arrays
            {
                int a[] = {5, 5, 5, 5, 5};
                int b[] = {5, 5, 5, 5, 5};
                int c[5];
                int expected[] = {10, 10, 10, 10, 10};
                sum_array_overlap(a, b, c, 5);
                for (int i = 0; i < 5; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 7: Output array overlaps with input arrays
            {
                int data[] = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
                sum_array_overlap(data, data + 5, data, 5);
                int expected[] = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
                for (int i = 0; i < 5; ++i) {
                    assert(data[i] == expected[i] + expected[i + 5]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void sum_array_overlap(int* a, int* b, int* c, int N) {
            for (int gid = 0; gid < N; ++gid) {
                c[gid] = a[gid] + b[gid];
            }
        }