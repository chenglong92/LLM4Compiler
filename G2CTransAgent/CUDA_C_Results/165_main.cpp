// original code(id = 165): 
 /*
__global__ void kernel_sum_backward ( float * db , float * dout , int r , int c ) { unsigned int tid = blockDim . x * blockIdx . x + threadIdx . x ; int N = c ; while ( tid < N ) { for ( int i = 0 ; i < r ; i ++ ) { db [ tid ] += dout [ i * c + tid ] ; } tid += gridDim . x * blockDim . x ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void kernel_sum_backward(float* db, float* dout, int r, int c) {
            for (int tid = 0; tid < c; ++tid) {
                float sum = 0.0f;
                for (int i = 0; i < r; ++i) {
                    sum += dout[i * c + tid];
                }
                db[tid] += sum;
            }
        }

        void test_kernel_sum_backward() {
            // Test case 1: Small matrix with known values
            {
                const int r = 2;
                const int c = 3;
                float db[c] = {0.0f, 0.0f, 0.0f};
                float dout[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};

                kernel_sum_backward(db, dout, r, c);

                assert(db[0] == 5.0f);  // 1 + 4
                assert(db[1] == 7.0f);  // 2 + 5
                assert(db[2] == 9.0f);  // 3 + 6
            }

            // Test case 2: Single row matrix
            {
                const int r = 1;
                const int c = 4;
                float db[c] = {1.0f, 2.0f, 3.0f, 4.0f};
                float dout[r * c] = {5.0f, 6.0f, 7.0f, 8.0f};

                kernel_sum_backward(db, dout, r, c);

                assert(db[0] == 6.0f);  // 1 + 5
                assert(db[1] == 8.0f);  // 2 + 6
                assert(db[2] == 10.0f); // 3 + 7
                assert(db[3] == 12.0f); // 4 + 8
            }

            // Test case 3: Single column matrix
            {
                const int r = 3;
                const int c = 1;
                float db[c] = {10.0f};
                float dout[r * c] = {1.0f, 2.0f, 3.0f};

                kernel_sum_backward(db, dout, r, c);

                assert(db[0] == 16.0f);  // 10 + (1 + 2 + 3)
            }

            // Test case 4: Large random matrix
            {
                const int r = 100;
                const int c = 50;
                float db[c];
                float dout[r * c];

                // Initialize with random values
                std::srand(std::time(0));
                for (int i = 0; i < c; ++i) {
                    db[i] = static_cast<float>(std::rand() % 100) / 10.0f;
                }
                for (int i = 0; i < r * c; ++i) {
                    dout[i] = static_cast<float>(std::rand() % 100) / 10.0f;
                }

                // Make a copy of db for verification
                float db_copy[c];
                for (int i = 0; i < c; ++i) {
                    db_copy[i] = db[i];
                }

                kernel_sum_backward(db, dout, r, c);

                // Verify the results
                for (int tid = 0; tid < c; ++tid) {
                    float sum = 0.0f;
                    for (int i = 0; i < r; ++i) {
                        sum += dout[i * c + tid];
                    }
                    assert(db[tid] == db_copy[tid] + sum);
                }
            }

            // Test case 5: Empty matrix (should do nothing)
            {
                const int r = 0;
                const int c = 0;
                float* db = nullptr;
                float* dout = nullptr;

                kernel_sum_backward(db, dout, r, c);
                // No assertions as function should handle gracefully
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_kernel_sum_backward();
            return 0;
        }