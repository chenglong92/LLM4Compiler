// original code(id = 17): 
 /*
__global__ void upsweep_scan ( int twod , int N , int * output ) { int twod1 = twod * 2 ; int idx = ( blockIdx . x * blockDim . x + threadIdx . x ) * twod1 ; if ( idx + twod1 - 1 < N ) output [ idx + twod1 - 1 ] += output [ idx + twod - 1 ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void upsweep_scan(int twod, int N, int* output) {
            int twod1 = twod * 2;
            const int blockDim = 256;
            int gridDim = (N + twod1 - 1) / (blockDim * twod1) + 1;
            
            for (int blockIdx = 0; blockIdx < gridDim; ++blockIdx) {
                for (int threadIdx = 0; threadIdx < blockDim; ++threadIdx) {
                    int idx = (blockIdx * blockDim + threadIdx) * twod1;
                    if (idx + twod1 - 1 < N) {
                        output[idx + twod1 - 1] += output[idx + twod - 1];
                    }
                }
            }
        }

        void test_case_1() {
            const int N = 512;
            const int twod = 1;
            int output[N] = {1};
            for (int i = 1; i < N; ++i) {
                output[i] = 1;
            }

            upsweep_scan(twod, N, output);

            for (int i = 1; i < N; i += 2) {
                assert(output[i] == 2);
            }
            std::cout << "Test case 1 passed!" << std::endl;
        }

        void test_case_2() {
            const int N = 1024;
            const int twod = 2;
            int output[N] = {1};
            for (int i = 1; i < N; ++i) {
                output[i] = 1;
            }

            upsweep_scan(twod, N, output);

            for (int i = 3; i < N; i += 4) {
                assert(output[i] == 2);
            }
            std::cout << "Test case 2 passed!" << std::endl;
        }

        void test_case_3() {
            const int N = 256;
            const int twod = 4;
            int output[N] = {1};
            for (int i = 1; i < N; ++i) {
                output[i] = 1;
            }

            upsweep_scan(twod, N, output);

            for (int i = 7; i < N; i += 8) {
                assert(output[i] == 2);
            }
            std::cout << "Test case 3 passed!" << std::endl;
        }

        void test_case_4() {
            const int N = 100;
            const int twod = 1;
            int output[N] = {1};
            for (int i = 1; i < N; ++i) {
                output[i] = 1;
            }

            upsweep_scan(twod, N, output);

            for (int i = 1; i < N; i += 2) {
                assert(output[i] == 2);
            }
            std::cout << "Test case 4 passed!" << std::endl;
        }

        void test_case_5() {
            const int N = 50;
            const int twod = 3;
            int output[N] = {1};
            for (int i = 1; i < N; ++i) {
                output[i] = 1;
            }

            upsweep_scan(twod, N, output);

            for (int i = 5; i < N; i += 6) {
                assert(output[i] == 2);
            }
            std::cout << "Test case 5 passed!" << std::endl;
        }

        int main() {
            test_case_1();
            test_case_2();
            test_case_3();
            test_case_4();
            test_case_5();

            return 0;
        }