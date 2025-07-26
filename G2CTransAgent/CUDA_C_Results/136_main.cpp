// original code(id = 136): 
 /*
__global__ void sumArrays ( float * A , float * B , float * C , const int N ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < N ) C [ i ] = A [ i ] + B [ i ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <limits>

        void sumArrays(float* A, float* B, float* C, const int N) {
            for (int i = 0; i < N; ++i) {
                C[i] = A[i] + B[i];
            }
        }

        int main() {
            // Test case 1: Basic addition
            {
                float A[] = {1.0f, 2.0f, 3.0f};
                float B[] = {4.0f, 5.0f, 6.0f};
                float C[3];
                const int N = 3;
                
                sumArrays(A, B, C, N);
                
                assert(C[0] == 5.0f);
                assert(C[1] == 7.0f);
                assert(C[2] == 9.0f);
            }

            // Test case 2: Empty arrays
            {
                float A[] = {};
                float B[] = {};
                float C[] = {};
                const int N = 0;
                
                sumArrays(A, B, C, N);
                // No assertions needed as no operations are performed
            }

            // Test case 3: Single element arrays
            {
                float A[] = {2.5f};
                float B[] = {-1.5f};
                float C[1];
                const int N = 1;
                
                sumArrays(A, B, C, N);
                
                assert(C[0] == 1.0f);
            }

            // Test case 4: Arrays with negative numbers
            {
                float A[] = {-1.0f, -2.0f, 3.0f};
                float B[] = {4.0f, -5.0f, -6.0f};
                float C[3];
                const int N = 3;
                
                sumArrays(A, B, C, N);
                
                assert(C[0] == 3.0f);
                assert(C[1] == -7.0f);
                assert(C[2] == -3.0f);
            }

            // Test case 5: Arrays with zero values
            {
                float A[] = {0.0f, 0.0f, 0.0f};
                float B[] = {0.0f, 0.0f, 0.0f};
                float C[3];
                const int N = 3;
                
                sumArrays(A, B, C, N);
                
                assert(C[0] == 0.0f);
                assert(C[1] == 0.0f);
                assert(C[2] == 0.0f);
            }

            // Test case 6: Large array
            {
                const int N = 1000;
                float A[N], B[N], C[N];
                
                for (int i = 0; i < N; ++i) {
                    A[i] = static_cast<float>(i);
                    B[i] = static_cast<float>(N - i);
                }
                
                sumArrays(A, B, C, N);
                
                for (int i = 0; i < N; ++i) {
                    assert(C[i] == static_cast<float>(N));
                }
            }

            // Test case 7: Extreme values
            {
                float max_val = std::numeric_limits<float>::max();
                float min_val = std::numeric_limits<float>::lowest();
                
                float A[] = {max_val, min_val, max_val/2};
                float B[] = {max_val, min_val, max_val/2};
                float C[3];
                const int N = 3;
                
                sumArrays(A, B, C, N);
                
                assert(C[0] == std::numeric_limits<float>::infinity());
                assert(C[1] == -std::numeric_limits<float>::infinity());
                assert(C[2] == max_val);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }