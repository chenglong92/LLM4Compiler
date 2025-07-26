// original code(id = 105): 
 /*
__global__ void fill_kernel ( int N , float ALPHA , float * X , int INCX ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) X [ i * INCX ] = ALPHA ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void fill_kernel(int N, float ALPHA, float* X, int INCX) {
            for (int i = 0; i < N; ++i) {
                X[i * INCX] = ALPHA;
            }
        }

        void print_array(float* arr, int size) {
            for (int i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        int main() {
            // Test case 1: Basic functionality
            {
                float X[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                fill_kernel(3, 10.0f, X, 1);
                assert(X[0] == 10.0f);
                assert(X[1] == 10.0f);
                assert(X[2] == 10.0f);
                assert(X[3] == 4.0f);
                assert(X[4] == 5.0f);
            }

            // Test case 2: N=0 (should do nothing)
            {
                float X[3] = {1.0f, 2.0f, 3.0f};
                fill_kernel(0, 5.0f, X, 1);
                assert(X[0] == 1.0f);
                assert(X[1] == 2.0f);
                assert(X[2] == 3.0f);
            }

            // Test case 3: Negative ALPHA
            {
                float X[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                fill_kernel(4, -3.5f, X, 1);
                assert(X[0] == -3.5f);
                assert(X[1] == -3.5f);
                assert(X[2] == -3.5f);
                assert(X[3] == -3.5f);
            }

            // Test case 4: INCX > 1
            {
                float X[10] = {0};
                fill_kernel(3, 7.0f, X, 3);
                assert(X[0] == 7.0f);
                assert(X[1] == 0.0f);
                assert(X[2] == 0.0f);
                assert(X[3] == 7.0f);
                assert(X[6] == 7.0f);
                assert(X[9] == 0.0f);
            }

            // Test case 5: Large N
            {
                const int SIZE = 1000;
                float* X = new float[SIZE];
                for (int i = 0; i < SIZE; ++i) {
                    X[i] = 0.0f;
                }
                fill_kernel(SIZE, 2.5f, X, 1);
                for (int i = 0; i < SIZE; ++i) {
                    assert(X[i] == 2.5f);
                }
                delete[] X;
            }

            // Test case 6: INCX=2 with odd N
            {
                float X[7] = {0};
                fill_kernel(3, 1.1f, X, 2);
                assert(X[0] == 1.1f);
                assert(X[1] == 0.0f);
                assert(X[2] == 1.1f);
                assert(X[3] == 0.0f);
                assert(X[4] == 1.1f);
                assert(X[5] == 0.0f);
                assert(X[6] == 0.0f);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }