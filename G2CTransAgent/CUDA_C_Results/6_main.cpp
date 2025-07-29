// original code(id = 6): 
 /*
__global__ void Kernel_Sum_backward_opt2 ( float * db , float * sum , int r_sum , int c ) { unsigned int j = blockDim . x * blockIdx . x + threadIdx . x ; if ( j >= c ) return ; float temp = 0 ; for ( int i = 0 ; i < r_sum ; i ++ ) { temp += sum [ i * c + j ] ; } db [ j ] = temp ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void Kernel_Sum_backward_opt2(float* db, float* sum, int r_sum, int c) {
            for (int j = 0; j < c; ++j) {
                float temp = 0;
                for (int i = 0; i < r_sum; ++i) {
                    temp += sum[i * c + j];
                }
                db[j] = temp;
            }
        }

        void test_normal_case() {
            const int r_sum = 3;
            const int c = 4;
            float sum[r_sum * c] = {1.0f, 2.0f, 3.0f, 4.0f,
                                    5.0f, 6.0f, 7.0f, 8.0f,
                                    9.0f, 10.0f, 11.0f, 12.0f};
            float db[c] = {0.0f};

            Kernel_Sum_backward_opt2(db, sum, r_sum, c);

            assert(db[0] == 15.0f);
            assert(db[1] == 18.0f);
            assert(db[2] == 21.0f);
            assert(db[3] == 24.0f);

            std::cout << "Normal case test passed." << std::endl;
        }

        void test_edge_case_empty_matrix() {
            const int r_sum = 0;
            const int c = 0;
            float* sum = nullptr;
            float* db = nullptr;

            Kernel_Sum_backward_opt2(db, sum, r_sum, c);

            std::cout << "Edge case (empty matrix) test passed." << std::endl;
        }

        void test_edge_case_single_row() {
            const int r_sum = 1;
            const int c = 3;
            float sum[r_sum * c] = {1.0f, 2.0f, 3.0f};
            float db[c] = {0.0f};

            Kernel_Sum_backward_opt2(db, sum, r_sum, c);

            assert(db[0] == 1.0f);
            assert(db[1] == 2.0f);
            assert(db[2] == 3.0f);

            std::cout << "Edge case (single row) test passed." << std::endl;
        }

        void test_edge_case_single_column() {
            const int r_sum = 4;
            const int c = 1;
            float sum[r_sum * c] = {1.0f, 2.0f, 3.0f, 4.0f};
            float db[c] = {0.0f};

            Kernel_Sum_backward_opt2(db, sum, r_sum, c);

            assert(db[0] == 10.0f);

            std::cout << "Edge case (single column) test passed." << std::endl;
        }

        int main() {
            test_normal_case();
            test_edge_case_empty_matrix();
            test_edge_case_single_row();
            test_edge_case_single_column();

            std::cout << "All tests passed successfully." << std::endl;
            return 0;
        }