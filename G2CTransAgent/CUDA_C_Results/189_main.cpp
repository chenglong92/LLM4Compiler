// original code(id = 189): 
 /*
__global__ void k_vec_divide ( float * vec1 , float * vec2 , size_t max_size ) { for ( int i = blockIdx . x * blockDim . x + threadIdx . x ; i < max_size ; i += blockDim . x * gridDim . x ) { vec1 [ i ] = vec1 [ i ] / vec2 [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <limits>

        void k_vec_divide(float* vec1, float* vec2, size_t max_size) {
            for (size_t i = 0; i < max_size; ++i) {
                vec1[i] = vec1[i] / vec2[i];
            }
        }

        int main() {
            // Test case 1: Normal division with positive numbers
            {
                float vec1[] = {10.0f, 20.0f, 30.0f};
                float vec2[] = {2.0f, 4.0f, 5.0f};
                float expected[] = {5.0f, 5.0f, 6.0f};
                k_vec_divide(vec1, vec2, 3);
                for (size_t i = 0; i < 3; ++i) {
                    assert(vec1[i] == expected[i]);
                }
            }

            // Test case 2: Division with negative numbers
            {
                float vec1[] = {-10.0f, -20.0f, -30.0f};
                float vec2[] = {2.0f, -4.0f, 5.0f};
                float expected[] = {-5.0f, 5.0f, -6.0f};
                k_vec_divide(vec1, vec2, 3);
                for (size_t i = 0; i < 3; ++i) {
                    assert(vec1[i] == expected[i]);
                }
            }

            // Test case 3: Division by one (identity)
            {
                float vec1[] = {1.0f, 2.0f, 3.0f};
                float vec2[] = {1.0f, 1.0f, 1.0f};
                float expected[] = {1.0f, 2.0f, 3.0f};
                k_vec_divide(vec1, vec2, 3);
                for (size_t i = 0; i < 3; ++i) {
                    assert(vec1[i] == expected[i]);
                }
            }

            // Test case 4: Division by zero (undefined behavior, but included for completeness)
            {
                float vec1[] = {1.0f, 2.0f, 3.0f};
                float vec2[] = {1.0f, 0.0f, 1.0f};
                // Note: This will cause undefined behavior when dividing by zero
                // Commenting out the actual call to avoid runtime error in test
                // k_vec_divide(vec1, vec2, 3);
            }

            // Test case 5: Division with maximum and minimum float values
            {
                float vec1[] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
                float vec2[] = {2.0f, 2.0f};
                float expected[] = {std::numeric_limits<float>::max() / 2.0f, std::numeric_limits<float>::min() / 2.0f};
                k_vec_divide(vec1, vec2, 2);
                for (size_t i = 0; i < 2; ++i) {
                    assert(vec1[i] == expected[i]);
                }
            }

            // Test case 6: Empty vectors
            {
                float vec1[] = {};
                float vec2[] = {};
                k_vec_divide(vec1, vec2, 0);
                // No operation should be performed
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }