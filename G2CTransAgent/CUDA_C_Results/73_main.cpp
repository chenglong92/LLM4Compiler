// original code(id = 73): 
 /*
__global__ void mul_kernel ( int N , float * X , int INCX , float * Y , int INCY ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) Y [ i * INCY ] *= X [ i * INCX ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void mul_kernel(int N, float* X, int INCX, float* Y, int INCY) {
            for (int i = 0; i < N; ++i) {
                Y[i * INCY] *= X[i * INCX];
            }
        }

        bool compareArrays(float* a, float* b, int size) {
            for (int i = 0; i < size; ++i) {
                if (fabs(a[i] - b[i]) > 1e-6) {
                    return false;
                }
            }
            return true;
        }

        void test_case_1() {
            const int N = 5;
            float X[N] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
            float Y[N] = {2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
            float expected[N] = {2.0f, 6.0f, 12.0f, 20.0f, 30.0f};
            
            mul_kernel(N, X, 1, Y, 1);
            
            assert(compareArrays(Y, expected, N));
            std::cout << "Test case 1 passed" << std::endl;
        }

        void test_case_2() {
            const int N = 3;
            float X[6] = {1.0f, 0.0f, 2.0f, 0.0f, 3.0f, 0.0f};
            float Y[6] = {2.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f};
            float expected[6] = {2.0f, 0.0f, 6.0f, 0.0f, 12.0f, 0.0f};
            
            mul_kernel(N, X, 2, Y, 2);
            
            assert(compareArrays(Y, expected, 6));
            std::cout << "Test case 2 passed" << std::endl;
        }

        void test_case_3() {
            const int N = 0;
            float X[1] = {1.0f};
            float Y[1] = {2.0f};
            float expected[1] = {2.0f};
            
            mul_kernel(N, X, 1, Y, 1);
            
            assert(compareArrays(Y, expected, 1));
            std::cout << "Test case 3 passed" << std::endl;
        }

        void test_case_4() {
            const int N = 4;
            float X[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
            float Y[4] = {2.0f, 3.0f, 4.0f, 5.0f};
            float expected[4] = {2.0f, 9.0f, 20.0f, 35.0f};
            
            mul_kernel(N, X, 2, Y, 1);
            
            assert(compareArrays(Y, expected, 4));
            std::cout << "Test case 4 passed" << std::endl;
        }

        void test_case_5() {
            const int N = 2;
            float X[4] = {1.0f, 2.0f, 3.0f, 4.0f};
            float Y[4] = {2.0f, 3.0f, 4.0f, 5.0f};
            float expected[4] = {2.0f, 9.0f, 4.0f, 5.0f};
            
            mul_kernel(N, X, 1, Y, 2);
            
            assert(compareArrays(Y, expected, 4));
            std::cout << "Test case 5 passed" << std::endl;
        }

        void test_case_6() {
            const int N = 1000;
            float* X = new float[N];
            float* Y = new float[N];
            float* expected = new float[N];
            
            for (int i = 0; i < N; ++i) {
                X[i] = 2.0f;
                Y[i] = i + 1.0f;
                expected[i] = 2.0f * (i + 1.0f);
            }
            
            mul_kernel(N, X, 1, Y, 1);
            
            assert(compareArrays(Y, expected, N));
            std::cout << "Test case 6 passed" << std::endl;
            
            delete[] X;
            delete[] Y;
            delete[] expected;
        }

        int main() {
            test_case_1();
            test_case_2();
            test_case_3();
            test_case_4();
            test_case_5();
            test_case_6();
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }