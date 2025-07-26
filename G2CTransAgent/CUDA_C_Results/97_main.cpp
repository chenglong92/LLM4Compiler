// original code(id = 97): 
 /*
__global__ void addMatrixGPU ( float * a , float * b , float * c , int N ) { int idx ; int j = threadIdx . x + blockIdx . x * blockDim . x ; int i = threadIdx . y + blockIdx . y * blockDim . y ; if ( ( i < N ) && ( j < N ) ) { idx = i * N + j ; a [ idx ] = b [ idx ] + c [ idx ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void addMatrixCPU(float* a, float* b, float* c, int N) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    int idx = i * N + j;
                    a[idx] = b[idx] + c[idx];
                }
            }
        }

        void testNormalCase() {
            const int N = 3;
            float a[N * N] = {0};
            float b[N * N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
            float c[N * N] = {9.0f, 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
            float expected[N * N] = {10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f};

            addMatrixCPU(a, b, c, N);

            for (int i = 0; i < N * N; ++i) {
                assert(a[i] == expected[i]);
            }
            std::cout << "Normal case test passed." << std::endl;
        }

        void testEdgeCase() {
            const int N = 1;
            float a[N * N] = {0};
            float b[N * N] = {5.5f};
            float c[N * N] = {4.5f};
            float expected[N * N] = {10.0f};

            addMatrixCPU(a, b, c, N);

            for (int i = 0; i < N * N; ++i) {
                assert(a[i] == expected[i]);
            }
            std::cout << "Edge case test passed." << std::endl;
        }

        void testRandomCase() {
            srand(time(0));
            const int N = 10;
            float a[N * N] = {0};
            float b[N * N];
            float c[N * N];
            float expected[N * N];

            for (int i = 0; i < N * N; ++i) {
                b[i] = static_cast<float>(rand() % 100);
                c[i] = static_cast<float>(rand() % 100);
                expected[i] = b[i] + c[i];
            }

            addMatrixCPU(a, b, c, N);

            for (int i = 0; i < N * N; ++i) {
                assert(a[i] == expected[i]);
            }
            std::cout << "Random case test passed." << std::endl;
        }

        int main() {
            testNormalCase();
            testEdgeCase();
            testRandomCase();
            return 0;
        }