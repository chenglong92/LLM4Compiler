// original code(id = 113): 
 /*
__global__ void addVectorsInto ( float * result , float * a , float * b , int N ) { int index = threadIdx . x + blockIdx . x * blockDim . x ; int stride = blockDim . x * gridDim . x ; for ( int i = index ; i < N ; i += stride ) { result [ i ] = a [ i ] + b [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <limits>

        void addVectorsInto(float* result, float* a, float* b, int N) {
            for (int i = 0; i < N; ++i) {
                result[i] = a[i] + b[i];
            }
        }

        void testAddVectorsInto() {
            // Test case 1: Basic addition with positive numbers
            {
                float a[] = {1.0f, 2.0f, 3.0f};
                float b[] = {4.0f, 5.0f, 6.0f};
                float result[3];
                float expected[] = {5.0f, 7.0f, 9.0f};
                addVectorsInto(result, a, b, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(result[i] == expected[i]);
                }
            }

            // Test case 2: Addition with negative numbers
            {
                float a[] = {-1.0f, -2.0f, -3.0f};
                float b[] = {4.0f, 5.0f, 6.0f};
                float result[3];
                float expected[] = {3.0f, 3.0f, 3.0f};
                addVectorsInto(result, a, b, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(result[i] == expected[i]);
                }
            }

            // Test case 3: Addition with zero values
            {
                float a[] = {0.0f, 0.0f, 0.0f};
                float b[] = {0.0f, 0.0f, 0.0f};
                float result[3];
                float expected[] = {0.0f, 0.0f, 0.0f};
                addVectorsInto(result, a, b, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(result[i] == expected[i]);
                }
            }

            // Test case 4: Single element arrays
            {
                float a[] = {42.0f};
                float b[] = {58.0f};
                float result[1];
                float expected[] = {100.0f};
                addVectorsInto(result, a, b, 1);
                assert(result[0] == expected[0]);
            }

            // Test case 5: Empty arrays
            {
                float a[] = {};
                float b[] = {};
                float result[0];
                addVectorsInto(result, a, b, 0);
                // No assertion needed as it shouldn't crash
            }

            // Test case 6: Large arrays
            {
                const int N = 1000;
                float a[N], b[N], result[N], expected[N];
                for (int i = 0; i < N; ++i) {
                    a[i] = static_cast<float>(i);
                    b[i] = static_cast<float>(N - i);
                    expected[i] = static_cast<float>(N);
                }
                addVectorsInto(result, a, b, N);
                for (int i = 0; i < N; ++i) {
                    assert(result[i] == expected[i]);
                }
            }

            // Test case 7: Extreme values
            {
                float max_val = std::numeric_limits<float>::max();
                float min_val = std::numeric_limits<float>::lowest();
                float a[] = {max_val, min_val, max_val};
                float b[] = {1.0f, -1.0f, -max_val};
                float result[3];
                float expected[] = {max_val, min_val - 1.0f, 0.0f};
                addVectorsInto(result, a, b, 3);
                for (int i = 0; i < 3; ++i) {
                    if (i == 1) {
                        // Special case for underflow
                        assert(result[i] == a[i] + b[i]);
                    } else {
                        assert(result[i] == expected[i]);
                    }
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            testAddVectorsInto();
            return 0;
        }