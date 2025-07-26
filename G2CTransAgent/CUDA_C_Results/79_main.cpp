// original code(id = 79): 
 /*
__global__ void mxm_1d ( double * a , const int m , double * b , const int n , double * c , const int p ) { const int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < m ) { for ( int k = 0 ; k < p ; k ++ ) { double s = 0.0 ; for ( int j = 0 ; j < n ; j ++ ) { s += a [ j * m + i ] * b [ k * n + j ] ; } c [ k * m + i ] = s ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void mxm_1d(double* a, const int m, double* b, const int n, double* c, const int p) {
            for (int i = 0; i < m; ++i) {
                for (int k = 0; k < p; ++k) {
                    double s = 0.0;
                    for (int j = 0; j < n; ++j) {
                        s += a[j * m + i] * b[k * n + j];
                    }
                    c[k * m + i] = s;
                }
            }
        }

        bool compareMatrices(const double* a, const double* b, int size, double epsilon = 1e-6) {
            for (int i = 0; i < size; ++i) {
                if (std::abs(a[i] - b[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        void test_basic_case() {
            const int m = 2, n = 3, p = 2;
            double a[m * n] = {1, 4, 2, 5, 3, 6}; // Column-major 2x3
            double b[n * p] = {7, 9, 11, 8, 10, 12}; // Column-major 3x2
            double expected[m * p] = {58, 139, 64, 154}; // Expected result 2x2
            double result[m * p];

            mxm_1d(a, m, b, n, result, p);

            assert(compareMatrices(result, expected, m * p));
        }

        void test_rectangular_matrices() {
            const int m = 3, n = 2, p = 4;
            double a[m * n] = {1, 3, 5, 2, 4, 6}; // Column-major 3x2
            double b[n * p] = {1, 3, 5, 7, 2, 4, 6, 8}; // Column-major 2x4
            double expected[m * p] = {5, 11, 17, 23, 11, 25, 39, 53, 17, 39, 61, 83}; // Expected 3x4
            double result[m * p];

            mxm_1d(a, m, b, n, result, p);

            assert(compareMatrices(result, expected, m * p));
        }

        void test_1x1_matrices() {
            const int m = 1, n = 1, p = 1;
            double a[m * n] = {5};
            double b[n * p] = {7};
            double expected[m * p] = {35};
            double result[m * p];

            mxm_1d(a, m, b, n, result, p);

            assert(compareMatrices(result, expected, m * p));
        }

        void test_empty_matrices() {
            const int m = 0, n = 0, p = 0;
            double* a = nullptr;
            double* b = nullptr;
            double* result = nullptr;

            mxm_1d(a, m, b, n, result, p);
            // No assertion needed as we just want to verify it doesn't crash
        }

        void test_larger_matrices() {
            const int m = 4, n = 3, p = 5;
            double a[m * n] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15}; // Column-major 4x3
            double b[n * p] = {1, 4, 7, 10, 13, 2, 5, 8, 11, 14, 3, 6, 9, 12, 15}; // Column-major 3x5
            double expected[m * p] = {14, 32, 50, 68, 86, 32, 77, 122, 167, 212, 
                                    50, 122, 194, 266, 338, 68, 167, 266, 365, 464};
            double result[m * p];

            mxm_1d(a, m, b, n, result, p);

            assert(compareMatrices(result, expected, m * p));
        }

        int main() {
            test_basic_case();
            test_rectangular_matrices();
            test_1x1_matrices();
            test_empty_matrices();
            test_larger_matrices();

            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }