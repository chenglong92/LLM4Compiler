// original code(id = 187): 
 /*
__global__ void addV ( int * a , int * b , int * c , int N ) { int index = threadIdx . x + blockIdx . x * blockDim . x ; if ( index < N ) { c [ index ] = a [ index ] + b [ index ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <climits>

        void addV(int* a, int* b, int* c, int N);

        int main() {
            // Test case 1: Basic addition with small arrays
            {
                int a[] = {1, 2, 3};
                int b[] = {4, 5, 6};
                int c[3];
                int expected[] = {5, 7, 9};
                addV(a, b, c, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 2: Empty arrays (N = 0)
            {
                int* a = nullptr;
                int* b = nullptr;
                int* c = nullptr;
                addV(a, b, c, 0);
                // No operation should be performed
            }

            // Test case 3: Single element arrays
            {
                int a[] = {10};
                int b[] = {-5};
                int c[1];
                addV(a, b, c, 1);
                assert(c[0] == 5);
            }

            // Test case 4: Arrays with negative numbers
            {
                int a[] = {-1, -2, -3};
                int b[] = {1, 2, 3};
                int c[3];
                int expected[] = {0, 0, 0};
                addV(a, b, c, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 5: Integer overflow scenario
            {
                int a[] = {INT_MAX, INT_MIN};
                int b[] = {1, -1};
                int c[2];
                addV(a, b, c, 2);
                assert(c[0] == INT_MIN); // Overflow wraps around
                assert(c[1] == INT_MAX); // Underflow wraps around
            }

            // Test case 6: Large arrays
            {
                const int N = 1000;
                int a[N], b[N], c[N];
                for (int i = 0; i < N; ++i) {
                    a[i] = i;
                    b[i] = i * 2;
                }
                addV(a, b, c, N);
                for (int i = 0; i < N; ++i) {
                    assert(c[i] == i * 3);
                }
            }

            // Test case 7: Arrays with alternating patterns
            {
                int a[] = {1, -1, 1, -1};
                int b[] = {-1, 1, -1, 1};
                int c[4];
                int expected[] = {0, 0, 0, 0};
                addV(a, b, c, 4);
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 8: Arrays with identical elements
            {
                int a[] = {5, 5, 5, 5};
                int b[] = {5, 5, 5, 5};
                int c[4];
                int expected[] = {10, 10, 10, 10};
                addV(a, b, c, 4);
                for (int i = 0; i < 4; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void addV(int* a, int* b, int* c, int N) {
            for (int index = 0; index < N; ++index) {
                c[index] = a[index] + b[index];
            }
        }