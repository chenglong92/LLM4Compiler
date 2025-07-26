// original code(id = 181): 
 /*
__global__ void MMDSelfComputeWithSum ( float * x_average , int size_x , float * distance_matrix ) { int block_id = blockIdx . x ; int thread_id = threadIdx . x ; for ( int i = block_id ; i < size_x ; i += gridDim . x ) { for ( int j = thread_id + i ; j < size_x ; j += blockDim . x ) { distance_matrix [ i * size_x + j ] = x_average [ i ] * x_average [ j ] ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void MMDSelfComputeWithSum(float* x_average, int size_x, float* distance_matrix) {
            for (int i = 0; i < size_x; ++i) {
                for (int j = i; j < size_x; ++j) {
                    distance_matrix[i * size_x + j] = x_average[i] * x_average[j];
                }
            }
        }

        void test_MMDSelfComputeWithSum() {
            // Test case 1: size_x = 1
            {
                float x_average[] = {2.0f};
                float distance_matrix[1] = {0.0f};
                MMDSelfComputeWithSum(x_average, 1, distance_matrix);
                assert(distance_matrix[0] == 4.0f);
            }

            // Test case 2: size_x = 2
            {
                float x_average[] = {1.0f, 2.0f};
                float distance_matrix[4] = {0.0f};
                MMDSelfComputeWithSum(x_average, 2, distance_matrix);
                assert(distance_matrix[0] == 1.0f); // [0][0]
                assert(distance_matrix[1] == 2.0f); // [0][1]
                assert(distance_matrix[2] == 0.0f); // [1][0] - not computed
                assert(distance_matrix[3] == 4.0f); // [1][1]
            }

            // Test case 3: size_x = 3
            {
                float x_average[] = {1.0f, 2.0f, 3.0f};
                float distance_matrix[9] = {0.0f};
                MMDSelfComputeWithSum(x_average, 3, distance_matrix);
                assert(distance_matrix[0] == 1.0f); // [0][0]
                assert(distance_matrix[1] == 2.0f); // [0][1]
                assert(distance_matrix[2] == 3.0f); // [0][2]
                assert(distance_matrix[3] == 0.0f); // [1][0] - not computed
                assert(distance_matrix[4] == 4.0f); // [1][1]
                assert(distance_matrix[5] == 6.0f); // [1][2]
                assert(distance_matrix[6] == 0.0f); // [2][0] - not computed
                assert(distance_matrix[7] == 0.0f); // [2][1] - not computed
                assert(distance_matrix[8] == 9.0f); // [2][2]
            }

            // Test case 4: size_x = 0 (edge case)
            {
                float* x_average = nullptr;
                float* distance_matrix = nullptr;
                MMDSelfComputeWithSum(x_average, 0, distance_matrix);
                // No assertions, just checking it doesn't crash
            }

            // Test case 5: Negative values
            {
                float x_average[] = {-1.0f, -2.0f};
                float distance_matrix[4] = {0.0f};
                MMDSelfComputeWithSum(x_average, 2, distance_matrix);
                assert(distance_matrix[0] == 1.0f); // [0][0]
                assert(distance_matrix[1] == 2.0f); // [0][1]
                assert(distance_matrix[2] == 0.0f); // [1][0] - not computed
                assert(distance_matrix[3] == 4.0f); // [1][1]
            }
        }

        int main() {
            test_MMDSelfComputeWithSum();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }