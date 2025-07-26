// original code(id = 108): 
 /*
__global__ void dmul_Scalar_matrix ( double * a , double value , double * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] * value ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void dmul_Scalar_matrix(double* a, double value, double* c, int N) {
            for (int idx = 0; idx < N; ++idx) {
                c[idx] = a[idx] * value;
            }
        }

        bool compareArrays(double* a, double* b, int N, double epsilon = 1e-6) {
            for (int i = 0; i < N; ++i) {
                if (fabs(a[i] - b[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        void test_dmul_Scalar_matrix() {
            // Test case 1: Basic multiplication with positive scalar
            {
                double a[] = {1.0, 2.0, 3.0};
                double c[3];
                double expected[] = {2.0, 4.0, 6.0};
                dmul_Scalar_matrix(a, 2.0, c, 3);
                assert(compareArrays(c, expected, 3));
            }

            // Test case 2: Multiplication with negative scalar
            {
                double a[] = {1.0, -2.0, 3.5};
                double c[3];
                double expected[] = {-0.5, 1.0, -1.75};
                dmul_Scalar_matrix(a, -0.5, c, 3);
                assert(compareArrays(c, expected, 3));
            }

            // Test case 3: Multiplication with zero scalar
            {
                double a[] = {1.0, 2.0, 3.0, 4.0};
                double c[4];
                double expected[] = {0.0, 0.0, 0.0, 0.0};
                dmul_Scalar_matrix(a, 0.0, c, 4);
                assert(compareArrays(c, expected, 4));
            }

            // Test case 4: Empty array (N = 0)
            {
                double a[] = {1.0, 2.0};
                double c[2];
                dmul_Scalar_matrix(a, 5.0, c, 0);
                // No assertion needed as function should handle N=0 gracefully
            }

            // Test case 5: Single element array
            {
                double a[] = {3.14};
                double c[1];
                double expected[] = {6.28};
                dmul_Scalar_matrix(a, 2.0, c, 1);
                assert(compareArrays(c, expected, 1));
            }

            // Test case 6: Large array
            {
                const int N = 1000;
                double a[N];
                double c[N];
                double expected[N];
                for (int i = 0; i < N; ++i) {
                    a[i] = i * 0.1;
                    expected[i] = a[i] * 1.5;
                }
                dmul_Scalar_matrix(a, 1.5, c, N);
                assert(compareArrays(c, expected, N));
            }

            // Test case 7: Array with zeros
            {
                double a[] = {0.0, 0.0, 0.0};
                double c[3];
                double expected[] = {0.0, 0.0, 0.0};
                dmul_Scalar_matrix(a, 5.0, c, 3);
                assert(compareArrays(c, expected, 3));
            }

            // Test case 8: Multiplication with identity scalar (1.0)
            {
                double a[] = {-1.0, 0.0, 1.0, 2.5};
                double c[4];
                double expected[] = {-1.0, 0.0, 1.0, 2.5};
                dmul_Scalar_matrix(a, 1.0, c, 4);
                assert(compareArrays(c, expected, 4));
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_dmul_Scalar_matrix();
            return 0;
        }