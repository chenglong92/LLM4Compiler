// original code(id = 175): 
 /*
__global__ void saxpi_nBlock ( int n , float a , float * x , float * y ) { int idx = threadIdx . x + ( blockIdx . x * blockDim . x ) ; if ( idx < n ) { y [ idx ] = a * x [ idx ] + y [ idx ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void saxpi_nBlock(int n, float a, float* x, float* y) {
            for (int i = 0; i < n; ++i) {
                y[i] = a * x[i] + y[i];
            }
        }

        void test_saxpi_nBlock() {
            // Test case 1: Basic test with n=3, a=2.0
            {
                int n = 3;
                float a = 2.0f;
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float expected[] = {6.0f, 9.0f, 12.0f};
                saxpi_nBlock(n, a, x, y);
                for (int i = 0; i < n; ++i) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 2: n=0 (should do nothing)
            {
                int n = 0;
                float a = 2.0f;
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float expected[] = {4.0f, 5.0f, 6.0f};
                saxpi_nBlock(n, a, x, y);
                for (int i = 0; i < 3; ++i) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 3: a=0.0 (y should remain unchanged)
            {
                int n = 3;
                float a = 0.0f;
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float expected[] = {4.0f, 5.0f, 6.0f};
                saxpi_nBlock(n, a, x, y);
                for (int i = 0; i < n; ++i) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 4: a=-1.0 (subtract x from y)
            {
                int n = 3;
                float a = -1.0f;
                float x[] = {1.0f, 2.0f, 3.0f};
                float y[] = {4.0f, 5.0f, 6.0f};
                float expected[] = {3.0f, 3.0f, 3.0f};
                saxpi_nBlock(n, a, x, y);
                for (int i = 0; i < n; ++i) {
                    assert(y[i] == expected[i]);
                }
            }

            // Test case 5: x and y are the same vector (in-place operation)
            {
                int n = 3;
                float a = 1.5f;
                float vec[] = {1.0f, 2.0f, 3.0f};
                float expected[] = {2.5f, 5.0f, 7.5f};
                saxpi_nBlock(n, a, vec, vec);
                for (int i = 0; i < n; ++i) {
                    assert(vec[i] == expected[i]);
                }
            }

            // Test case 6: Large n
            {
                const int n = 1000;
                float a = 0.5f;
                float x[n];
                float y[n];
                float expected[n];
                for (int i = 0; i < n; ++i) {
                    x[i] = static_cast<float>(i);
                    y[i] = static_cast<float>(i * 2);
                    expected[i] = a * x[i] + y[i];
                }
                saxpi_nBlock(n, a, x, y);
                for (int i = 0; i < n; ++i) {
                    assert(y[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_saxpi_nBlock();
            return 0;
        }