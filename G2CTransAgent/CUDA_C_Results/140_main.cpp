// original code(id = 140): 
 /*
__global__ void add ( int n , float * x , float * y ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; for ( int i = index ; i < n ; i ++ ) { y [ i ] = x [ i ] + y [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void add(int n, float* x, float* y) {
            for (int i = 0; i < n; i++) {
                y[i] = x[i] + y[i];
            }
        }

        void test_add() {
            // Test case 1: Normal case with positive numbers
            {
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float expected[] = {5.0f, 7.0f, 9.0f};
                add(3, x, y);
                for (int i = 0; i < 3; i++) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 2: Normal case with negative numbers
            {
                float x[] = {-1.0f, -2.0f, -3.0f};
                float y[] = {-4.0f, -5.0f, -6.0f};
                float expected[] = {-5.0f, -7.0f, -9.0f};
                add(3, x, y);
                for (int i = 0; i < 3; i++) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 3: Mixed positive and negative numbers
            {
                float x[] = {-1.0f, 2.0f, -3.0f};
                float y[] = {4.0f, -5.0f, 6.0f};
                float expected[] = {3.0f, -3.0f, 3.0f};
                add(3, x, y);
                for (int i = 0; i < 3; i++) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 4: Zero elements (n = 0)
            {
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float original_y[] = {4.0f, 5.0f, 6.0f};
                add(0, x, y);
                for (int i = 0; i < 3; i++) {
                    assert(y[i] == original_y[i]);
                }
            }

            // Test case 5: Single element
            {
                float x[] = {1.5f};
                float y[] = {2.5f};
                float expected[] = {4.0f};
                add(1, x, y);
                assert(y[0] == expected[0]);
            }

            // Test case 6: x and y point to same array
            {
                float arr[] = {1.0f, 2.0f, 3.0f};
                float expected[] = {2.0f, 4.0f, 6.0f};
                add(3, arr, arr);
                for (int i = 0; i < 3; i++) {
                    assert(arr[i] == expected[i]);
                }
            }

            // Test case 7: Floating point precision
            {
                float x[] = {0.1f, 0.2f, 0.3f};
                float y[] = {0.4f, 0.5f, 0.6f};
                float expected[] = {0.5f, 0.7f, 0.9f};
                add(3, x, y);
                for (int i = 0; i < 3; i++) {
                    assert(y[i] >= expected[i] - 0.0001f && y[i] <= expected[i] + 0.0001f);
                }
            }
        }

        int main() {
            test_add();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }