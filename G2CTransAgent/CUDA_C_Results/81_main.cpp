// original code(id = 81): 
 /*
__global__ void MMDOuterProdComputeWithSum ( float * x_average , int size_x , float * x_outer_prod ) { int block_id = blockIdx . x ; int thread_id = threadIdx . x ; for ( int i = block_id * blockDim . x + thread_id ; i < size_x ; i += gridDim . x * blockDim . x ) { x_outer_prod [ i ] = x_average [ i ] * x_average [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void MMDOuterProdComputeWithSum(float* x_average, int size_x, float* x_outer_prod) {
            for (int i = 0; i < size_x; ++i) {
                x_outer_prod[i] = x_average[i] * x_average[i];
            }
        }

        void test_case_1() {
            const int size = 5;
            float x_avg[size] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
            float x_prod[size];
            float expected[size] = {1.0f, 4.0f, 9.0f, 16.0f, 25.0f};

            MMDOuterProdComputeWithSum(x_avg, size, x_prod);

            for (int i = 0; i < size; ++i) {
                assert(fabs(x_prod[i] - expected[i]) < 1e-6f);
            }
            std::cout << "Test case 1 passed." << std::endl;
        }

        void test_case_2() {
            const int size = 4;
            float x_avg[size] = {-1.0f, -2.0f, -3.0f, -4.0f};
            float x_prod[size];
            float expected[size] = {1.0f, 4.0f, 9.0f, 16.0f};

            MMDOuterProdComputeWithSum(x_avg, size, x_prod);

            for (int i = 0; i < size; ++i) {
                assert(fabs(x_prod[i] - expected[i]) < 1e-6f);
            }
            std::cout << "Test case 2 passed." << std::endl;
        }

        void test_case_3() {
            const int size = 3;
            float x_avg[size] = {0.0f, 0.0f, 0.0f};
            float x_prod[size];
            float expected[size] = {0.0f, 0.0f, 0.0f};

            MMDOuterProdComputeWithSum(x_avg, size, x_prod);

            for (int i = 0; i < size; ++i) {
                assert(fabs(x_prod[i] - expected[i]) < 1e-6f);
            }
            std::cout << "Test case 3 passed." << std::endl;
        }

        void test_case_4() {
            const int size = 6;
            float x_avg[size] = {-2.5f, 0.0f, 1.5f, -3.0f, 4.0f, 0.5f};
            float x_prod[size];
            float expected[size] = {6.25f, 0.0f, 2.25f, 9.0f, 16.0f, 0.25f};

            MMDOuterProdComputeWithSum(x_avg, size, x_prod);

            for (int i = 0; i < size; ++i) {
                assert(fabs(x_prod[i] - expected[i]) < 1e-6f);
            }
            std::cout << "Test case 4 passed." << std::endl;
        }

        void test_case_5() {
            const int size = 0;
            float* x_avg = nullptr;
            float* x_prod = nullptr;

            // Should not crash or produce any errors
            MMDOuterProdComputeWithSum(x_avg, size, x_prod);
            std::cout << "Test case 5 passed." << std::endl;
        }

        void test_case_6() {
            const int size = 1;
            float x_avg[size] = {2.0f};
            float x_prod[size];
            float expected[size] = {4.0f};

            MMDOuterProdComputeWithSum(x_avg, size, x_prod);

            assert(fabs(x_prod[0] - expected[0]) < 1e-6f);
            std::cout << "Test case 6 passed." << std::endl;
        }

        int main() {
            test_case_1();
            test_case_2();
            test_case_3();
            test_case_4();
            test_case_5();
            test_case_6();

            std::cout << "All test cases passed successfully!" << std::endl;
            return 0;
        }