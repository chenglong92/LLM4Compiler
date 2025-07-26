// original code(id = 6): 
 /*
__global__ void Kernel_Sum_backward_opt2 ( float * db , float * sum , int r_sum , int c ) { unsigned int j = blockDim . x * blockIdx . x + threadIdx . x ; if ( j >= c ) return ; float temp = 0 ; for ( int i = 0 ; i < r_sum ; i ++ ) { temp += sum [ i * c + j ] ; } db [ j ] = temp ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void Kernel_Sum_backward_opt2(float* db, float* sum, int r_sum, int c) {
            for (int j = 0; j < c; ++j) {
                float temp = 0;
                for (int i = 0; i < r_sum; ++i) {
                    temp += sum[i * c + j];
                }
                db[j] = temp;
            }
        }

        int main() {
            // Test case 1: Single row and single column
            {
                float db[1] = {0};
                float sum[1] = {5.0f};
                int r_sum = 1;
                int c = 1;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                assert(db[0] == 5.0f);
            }

            // Test case 2: Multiple rows and single column
            {
                float db[1] = {0};
                float sum[] = {1.0f, 2.0f, 3.0f};
                int r_sum = 3;
                int c = 1;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                assert(db[0] == 6.0f);
            }

            // Test case 3: Single row and multiple columns
            {
                float db[3] = {0};
                float sum[] = {1.0f, 2.0f, 3.0f};
                int r_sum = 1;
                int c = 3;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                assert(db[0] == 1.0f);
                assert(db[1] == 2.0f);
                assert(db[2] == 3.0f);
            }

            // Test case 4: Multiple rows and multiple columns
            {
                float db[2] = {0};
                float sum[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                int r_sum = 3;
                int c = 2;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                assert(db[0] == 9.0f); // 1 + 3 + 5
                assert(db[1] == 12.0f); // 2 + 4 + 6
            }

            // Test case 5: Empty rows (r_sum = 0)
            {
                float db[2] = {0};
                float sum[] = {1.0f, 2.0f};
                int r_sum = 0;
                int c = 2;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                assert(db[0] == 0.0f);
                assert(db[1] == 0.0f);
            }

            // Test case 6: Empty columns (c = 0)
            {
                float db[1] = {0};
                float sum[] = {1.0f, 2.0f, 3.0f};
                int r_sum = 3;
                int c = 0;
                Kernel_Sum_backward_opt2(db, sum, r_sum, c);
                // No assertion as db is not modified when c = 0
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }