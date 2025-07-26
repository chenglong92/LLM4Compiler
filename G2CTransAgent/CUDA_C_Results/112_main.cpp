// original code(id = 112): 
 /*
__global__ void solveLowerKernel ( const double * lower , const double * b , double * buf , int dim , int n ) { int k = blockIdx . x * blockDim . x + threadIdx . x ; if ( k < n ) { for ( int i = 0 ; i < dim ; i ++ ) { double val = b [ k * dim + i ] ; for ( int j = 0 ; j < i ; j ++ ) { val -= lower [ i * dim + j ] * buf [ k * dim + j ] ; } buf [ k * dim + i ] = val / lower [ i * dim + i ] ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void solveLowerKernel(const double* lower, const double* b, double* buf, int dim, int n);

        void test1() {
            const int dim = 2;
            const int n = 1;
            double lower[dim * dim] = {2.0, 0.0,
                                      1.0, 3.0};
            double b[dim * n] = {4.0, 7.0};
            double buf[dim * n] = {0.0};
            double expected[dim * n] = {2.0, (7.0 - 1.0 * 2.0) / 3.0};

            solveLowerKernel(lower, b, buf, dim, n);

            for (int i = 0; i < dim * n; ++i) {
                assert(fabs(buf[i] - expected[i]) < 1e-10);
            }
        }

        void test2() {
            const int dim = 3;
            const int n = 2;
            double lower[dim * dim] = {1.0, 0.0, 0.0,
                                      2.0, 3.0, 0.0,
                                      4.0, 5.0, 6.0};
            double b[dim * n] = {1.0, 5.0, 15.0,
                                2.0, 8.0, 24.0};
            double buf[dim * n] = {0.0};
            double expected[dim * n] = {1.0, (5.0 - 2.0 * 1.0)/3.0, (15.0 - 4.0*1.0 - 5.0*((5.0 - 2.0 * 1.0)/3.0))/6.0,
                                       2.0, (8.0 - 2.0 * 2.0)/3.0, (24.0 - 4.0*2.0 - 5.0*((8.0 - 2.0 * 2.0)/3.0))/6.0};

            solveLowerKernel(lower, b, buf, dim, n);

            for (int i = 0; i < dim * n; ++i) {
                assert(fabs(buf[i] - expected[i]) < 1e-10);
            }
        }

        void test3() {
            const int dim = 1;
            const int n = 1;
            double lower[dim * dim] = {5.0};
            double b[dim * n] = {10.0};
            double buf[dim * n] = {0.0};
            double expected[dim * n] = {2.0};

            solveLowerKernel(lower, b, buf, dim, n);

            assert(fabs(buf[0] - expected[0]) < 1e-10);
        }

        void test4() {
            const int dim = 4;
            const int n = 3;
            double lower[dim * dim] = {1.0, 0.0, 0.0, 0.0,
                                      1.0, 1.0, 0.0, 0.0,
                                      1.0, 1.0, 1.0, 0.0,
                                      1.0, 1.0, 1.0, 1.0};
            double b[dim * n] = {1.0, 2.0, 3.0, 4.0,
                                2.0, 4.0, 6.0, 8.0,
                                3.0, 6.0, 9.0, 12.0};
            double buf[dim * n] = {0.0};
            double expected[dim * n] = {1.0, 1.0, 1.0, 1.0,
                                       2.0, 2.0, 2.0, 2.0,
                                       3.0, 3.0, 3.0, 3.0};

            solveLowerKernel(lower, b, buf, dim, n);

            for (int i = 0; i < dim * n; ++i) {
                assert(fabs(buf[i] - expected[i]) < 1e-10);
            }
        }

        void test5() {
            const int dim = 2;
            const int n = 1;
            double lower[dim * dim] = {1.0, 0.0,
                                      0.5, 0.5};
            double b[dim * n] = {1.0, 1.0};
            double buf[dim * n] = {0.0};
            double expected[dim * n] = {1.0, (1.0 - 0.5 * 1.0)/0.5};

            solveLowerKernel(lower, b, buf, dim, n);

            for (int i = 0; i < dim * n; ++i) {
                assert(fabs(buf[i] - expected[i]) < 1e-10);
            }
        }

        int main() {
            test1();
            test2();
            test3();
            test4();
            test5();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }

        void solveLowerKernel(const double* lower, const double* b, double* buf, int dim, int n) {
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < dim; ++i) {
                    double val = b[k * dim + i];
                    for (int j = 0; j < i; ++j) {
                        val -= lower[i * dim + j] * buf[k * dim + j];
                    }
                    buf[k * dim + i] = val / lower[i * dim + i];
                }
            }
        }