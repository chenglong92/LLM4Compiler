// original code(id = 53): 
 /*
__global__ void squareKernel ( float * d_in , float * d_out , int N ) { const unsigned int lid = threadIdx . x ; const unsigned int gid = blockIdx . x * blockDim . x + lid ; if ( gid < N ) { d_out [ gid ] = pow ( d_in [ gid ] / ( d_in [ gid ] - 2.3 ) , 3 ) ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <limits>
        #include <cassert>

        void squareKernel(float* d_in, float* d_out, int N);

        int main() {
            // Test case 1: Normal positive numbers
            {
                const int N = 5;
                float input[N] = {1.0f, 3.0f, 5.0f, 10.0f, 100.0f};
                float output[N];
                float expected[N];
                
                for (int i = 0; i < N; ++i) {
                    expected[i] = pow(input[i] / (input[i] - 2.3f), 3);
                }
                
                squareKernel(input, output, N);
                
                for (int i = 0; i < N; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 2: Negative numbers
            {
                const int N = 4;
                float input[N] = {-1.0f, -3.0f, -5.0f, -10.0f};
                float output[N];
                float expected[N];
                
                for (int i = 0; i < N; ++i) {
                    expected[i] = pow(input[i] / (input[i] - 2.3f), 3);
                }
                
                squareKernel(input, output, N);
                
                for (int i = 0; i < N; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 3: Zero input
            {
                const int N = 1;
                float input[N] = {0.0f};
                float output[N];
                float expected[N] = {pow(0.0f / (0.0f - 2.3f), 3)};
                
                squareKernel(input, output, N);
                
                assert(fabs(output[0] - expected[0]) < 1e-6f);
            }

            // Test case 4: Input close to 2.3 (but not exactly 2.3)
            {
                const int N = 2;
                float input[N] = {2.2999999f, 2.3000001f};
                float output[N];
                float expected[N];
                
                for (int i = 0; i < N; ++i) {
                    expected[i] = pow(input[i] / (input[i] - 2.3f), 3);
                }
                
                squareKernel(input, output, N);
                
                for (int i = 0; i < N; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 5: Large numbers
            {
                const int N = 3;
                float input[N] = {1e10f, -1e10f, 1e20f};
                float output[N];
                float expected[N];
                
                for (int i = 0; i < N; ++i) {
                    expected[i] = pow(input[i] / (input[i] - 2.3f), 3);
                }
                
                squareKernel(input, output, N);
                
                for (int i = 0; i < N; ++i) {
                    assert(fabs(output[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 6: NaN and infinity
            {
                const int N = 4;
                float input[N] = {std::numeric_limits<float>::infinity(),
                                 -std::numeric_limits<float>::infinity(),
                                 std::numeric_limits<float>::quiet_NaN(),
                                 std::numeric_limits<float>::signaling_NaN()};
                float output[N];
                
                squareKernel(input, output, N);
                
                // Check infinity cases
                assert(output[0] == 1.0f);
                assert(output[1] == 1.0f);
                
                // Check NaN cases - output should be NaN
                assert(std::isnan(output[2]));
                assert(std::isnan(output[3]));
            }

            // Test case 7: Empty array
            {
                const int N = 0;
                float* input = nullptr;
                float* output = nullptr;
                
                squareKernel(input, output, N);
                // No assertion needed, just checking it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void squareKernel(float* d_in, float* d_out, int N) {
            for (int gid = 0; gid < N; ++gid) {
                d_out[gid] = pow(d_in[gid] / (d_in[gid] - 2.3f), 3);
            }
        }