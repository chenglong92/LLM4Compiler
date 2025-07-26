// original code(id = 91): 
 /*
__global__ void scal_kernel ( int N , float ALPHA , float * X , int INCX ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < N ) X [ i * INCX ] *= ALPHA ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void scal_kernel(int N, float ALPHA, float* X, int INCX) {
            for (int i = 0; i < N; ++i) {
                X[i * INCX] *= ALPHA;
            }
        }

        void print_array(float* arr, int size) {
            for (int i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        bool arrays_equal(float* a, float* b, int size, float epsilon = 1e-6) {
            for (int i = 0; i < size; ++i) {
                if (fabs(a[i] - b[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        void test_case_1() {
            // Basic test with positive ALPHA and INCX = 1
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {2.0f, 4.0f, 6.0f, 8.0f};
            scal_kernel(4, 2.0f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 1 passed" << std::endl;
        }

        void test_case_2() {
            // Test with negative ALPHA and INCX = 1
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {-1.0f, -2.0f, -3.0f, -4.0f};
            scal_kernel(4, -1.0f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 2 passed" << std::endl;
        }

        void test_case_3() {
            // Test with zero ALPHA
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {0.0f, 0.0f, 0.0f, 0.0f};
            scal_kernel(4, 0.0f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 3 passed" << std::endl;
        }

        void test_case_4() {
            // Test with INCX = 2
            float X[] = {1.0f, 0.0f, 2.0f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f};
            float expected[] = {2.0f, 0.0f, 4.0f, 0.0f, 6.0f, 0.0f, 8.0f, 0.0f};
            scal_kernel(4, 2.0f, X, 2);
            assert(arrays_equal(X, expected, 8));
            std::cout << "Test case 4 passed" << std::endl;
        }

        void test_case_5() {
            // Test with N = 0 (should do nothing)
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
            scal_kernel(0, 2.0f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 5 passed" << std::endl;
        }

        void test_case_6() {
            // Test with very small ALPHA
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {1e-6f, 2e-6f, 3e-6f, 4e-6f};
            scal_kernel(4, 1e-6f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 6 passed" << std::endl;
        }

        void test_case_7() {
            // Test with very large ALPHA
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {1e6f, 2e6f, 3e6f, 4e6f};
            scal_kernel(4, 1e6f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 7 passed" << std::endl;
        }

        void test_case_8() {
            // Test with INCX = 0 (undefined behavior, but should test)
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float original[] = {1.0f, 2.0f, 3.0f, 4.0f};
            scal_kernel(4, 2.0f, X, 0);
            // Can't assert anything meaningful here, just checking it doesn't crash
            std::cout << "Test case 8 executed (undefined behavior case)" << std::endl;
        }

        void test_case_9() {
            // Test with large N
            const int N = 1000;
            float* X = new float[N];
            float* expected = new float[N];
            for (int i = 0; i < N; ++i) {
                X[i] = i + 1.0f;
                expected[i] = (i + 1.0f) * 1.5f;
            }
            scal_kernel(N, 1.5f, X, 1);
            assert(arrays_equal(X, expected, N));
            delete[] X;
            delete[] expected;
            std::cout << "Test case 9 passed" << std::endl;
        }

        void test_case_10() {
            // Test with fractional ALPHA
            float X[] = {1.0f, 2.0f, 3.0f, 4.0f};
            float expected[] = {0.5f, 1.0f, 1.5f, 2.0f};
            scal_kernel(4, 0.5f, X, 1);
            assert(arrays_equal(X, expected, 4));
            std::cout << "Test case 10 passed" << std::endl;
        }

        int main() {
            test_case_1();
            test_case_2();
            test_case_3();
            test_case_4();
            test_case_5();
            test_case_6();
            test_case_7();
            test_case_8();
            test_case_9();
            test_case_10();
            
            std::cout << "All test cases completed" << std::endl;
            return 0;
        }