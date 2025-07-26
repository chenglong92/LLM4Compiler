// original code(id = 203): 
 /*
__global__ void update_x ( double * x , double * a , double * b , int n ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = gridDim . x * blockDim . x ; for ( int i = index ; i < n ; i += stride ) { x [ i ] = 2. / 3. * a [ i ] / b [ i ] + 1. / 3. * x [ i ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <limits>

        void update_x(double* x, double* a, double* b, int n) {
            for (int i = 0; i < n; ++i) {
                x[i] = 2. / 3. * a[i] / b[i] + 1. / 3. * x[i];
            }
        }

        bool compare_doubles(double a, double b, double epsilon = 1e-6) {
            return std::fabs(a - b) < epsilon;
        }

        void print_array(double* arr, int n, const char* name) {
            std::cout << name << ": [";
            for (int i = 0; i < n; ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << arr[i];
            }
            std::cout << "]" << std::endl;
        }

        void test_case(double* x, double* a, double* b, int n, double* expected, const char* name) {
            update_x(x, a, b, n);
            bool passed = true;
            for (int i = 0; i < n; ++i) {
                if (!compare_doubles(x[i], expected[i])) {
                    passed = false;
                    break;
                }
            }
            std::cout << "Test " << name << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
            if (!passed) {
                print_array(x, n, "Actual");
                print_array(expected, n, "Expected");
            }
        }

        int main() {
            // Test case 1: Normal case with positive values
            {
                double x[] = {1.0, 2.0, 3.0};
                double a[] = {3.0, 6.0, 9.0};
                double b[] = {2.0, 3.0, 6.0};
                double expected[] = {
                    2./3.*3.0/2.0 + 1./3.*1.0,
                    2./3.*6.0/3.0 + 1./3.*2.0,
                    2./3.*9.0/6.0 + 1./3.*3.0
                };
                test_case(x, a, b, 3, expected, "Positive values");
            }

            // Test case 2: Negative values
            {
                double x[] = {-1.0, -2.0, -3.0};
                double a[] = {-3.0, -6.0, -9.0};
                double b[] = {2.0, 3.0, 6.0};
                double expected[] = {
                    2./3.*-3.0/2.0 + 1./3.*-1.0,
                    2./3.*-6.0/3.0 + 1./3.*-2.0,
                    2./3.*-9.0/6.0 + 1./3.*-3.0
                };
                test_case(x, a, b, 3, expected, "Negative values");
            }

            // Test case 3: Mixed positive and negative values
            {
                double x[] = {1.0, -2.0, 0.0};
                double a[] = {-3.0, 6.0, 0.0};
                double b[] = {2.0, -3.0, 1.0};
                double expected[] = {
                    2./3.*-3.0/2.0 + 1./3.*1.0,
                    2./3.*6.0/-3.0 + 1./3.*-2.0,
                    2./3.*0.0/1.0 + 1./3.*0.0
                };
                test_case(x, a, b, 3, expected, "Mixed values");
            }

            // Test case 4: Edge case with n = 0
            {
                double x[] = {1.0};
                double a[] = {2.0};
                double b[] = {3.0};
                double expected[] = {1.0};
                test_case(x, a, b, 0, expected, "Empty arrays");
            }

            // Test case 5: Very small values
            {
                double x[] = {1e-20, -1e-20};
                double a[] = {2e-20, -2e-20};
                double b[] = {3e-20, -3e-20};
                double expected[] = {
                    2./3.*2e-20/3e-20 + 1./3.*1e-20,
                    2./3.*-2e-20/-3e-20 + 1./3.*-1e-20
                };
                test_case(x, a, b, 2, expected, "Very small values");
            }

            // Test case 6: Very large values
            {
                double x[] = {1e20, -1e20};
                double a[] = {2e20, -2e20};
                double b[] = {3e20, -3e20};
                double expected[] = {
                    2./3.*2e20/3e20 + 1./3.*1e20,
                    2./3.*-2e20/-3e20 + 1./3.*-1e20
                };
                test_case(x, a, b, 2, expected, "Very large values");
            }

            // Test case 7: Zero in a array
            {
                double x[] = {1.0, 2.0};
                double a[] = {0.0, 0.0};
                double b[] = {1.0, 2.0};
                double expected[] = {
                    2./3.*0.0/1.0 + 1./3.*1.0,
                    2./3.*0.0/2.0 + 1./3.*2.0
                };
                test_case(x, a, b, 2, expected, "Zero in a array");
            }

            return 0;
        }