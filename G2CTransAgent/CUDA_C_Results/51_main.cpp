// original code(id = 51): 
 /*
__global__ void compute_b_minus_Rx ( double * out , double * x , double * b , double * cotans , int * neighbors , int meshStride , int n ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; int stride = gridDim . x * blockDim . x ; for ( int i = index ; i < n ; i += stride ) { out [ i ] = b [ i ] ; for ( int iN = 0 ; iN < meshStride ; ++ iN ) { int neighbor = neighbors [ i * meshStride + iN ] ; double weight = cotans [ i * meshStride + iN ] ; out [ i ] += weight * x [ neighbor ] ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void compute_b_minus_Rx(double* out, double* x, double* b, double* cotans, int* neighbors, int meshStride, int n) {
            for (int i = 0; i < n; ++i) {
                out[i] = b[i];
                for (int iN = 0; iN < meshStride; ++iN) {
                    int neighbor = neighbors[i * meshStride + iN];
                    double weight = cotans[i * meshStride + iN];
                    out[i] -= weight * x[neighbor];
                }
            }
        }

        void test_basic_case() {
            const int n = 3;
            const int meshStride = 2;
            double out[n] = {0};
            double x[n] = {1.0, 2.0, 3.0};
            double b[n] = {10.0, 20.0, 30.0};
            double cotans[n * meshStride] = {0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
            int neighbors[n * meshStride] = {1, 2, 0, 2, 0, 1};

            compute_b_minus_Rx(out, x, b, cotans, neighbors, meshStride, n);

            assert(fabs(out[0] - (10.0 - (0.5*2.0 + 1.0*3.0))) < 1e-10);
            assert(fabs(out[1] - (20.0 - (1.5*1.0 + 2.0*3.0))) < 1e-10);
            assert(fabs(out[2] - (30.0 - (2.5*1.0 + 3.0*2.0))) < 1e-10);
        }

        void test_zero_case() {
            const int n = 2;
            const int meshStride = 2;
            double out[n] = {0};
            double x[n] = {0.0, 0.0};
            double b[n] = {0.0, 0.0};
            double cotans[n * meshStride] = {0.0, 0.0, 0.0, 0.0};
            int neighbors[n * meshStride] = {0, 1, 0, 1};

            compute_b_minus_Rx(out, x, b, cotans, neighbors, meshStride, n);

            assert(fabs(out[0] - 0.0) < 1e-10);
            assert(fabs(out[1] - 0.0) < 1e-10);
        }

        void test_single_element() {
            const int n = 1;
            const int meshStride = 1;
            double out[n] = {0};
            double x[n] = {5.0};
            double b[n] = {10.0};
            double cotans[n * meshStride] = {2.0};
            int neighbors[n * meshStride] = {0};

            compute_b_minus_Rx(out, x, b, cotans, neighbors, meshStride, n);

            assert(fabs(out[0] - (10.0 - 2.0*5.0)) < 1e-10);
        }

        void test_self_reference() {
            const int n = 2;
            const int meshStride = 2;
            double out[n] = {0};
            double x[n] = {1.0, 2.0};
            double b[n] = {5.0, 10.0};
            double cotans[n * meshStride] = {1.0, 1.0, 2.0, 2.0};
            int neighbors[n * meshStride] = {0, 0, 1, 1};

            compute_b_minus_Rx(out, x, b, cotans, neighbors, meshStride, n);

            assert(fabs(out[0] - (5.0 - (1.0*1.0 + 1.0*1.0))) < 1e-10);
            assert(fabs(out[1] - (10.0 - (2.0*2.0 + 2.0*2.0))) < 1e-10);
        }

        void test_varying_mesh_stride() {
            const int n = 4;
            const int meshStride = 3;
            double out[n] = {0};
            double x[n] = {1.0, 2.0, 3.0, 4.0};
            double b[n] = {10.0, 20.0, 30.0, 40.0};
            double cotans[n * meshStride] = {
                0.5, 1.0, 1.5,
                2.0, 2.5, 3.0,
                3.5, 4.0, 4.5,
                5.0, 5.5, 6.0
            };
            int neighbors[n * meshStride] = {
                1, 2, 3,
                0, 2, 3,
                0, 1, 3,
                0, 1, 2
            };

            compute_b_minus_Rx(out, x, b, cotans, neighbors, meshStride, n);

            assert(fabs(out[0] - (10.0 - (0.5*2.0 + 1.0*3.0 + 1.5*4.0))) < 1e-10);
            assert(fabs(out[1] - (20.0 - (2.0*1.0 + 2.5*3.0 + 3.0*4.0))) < 1e-10);
            assert(fabs(out[2] - (30.0 - (3.5*1.0 + 4.0*2.0 + 4.5*4.0))) < 1e-10);
            assert(fabs(out[3] - (40.0 - (5.0*1.0 + 5.5*2.0 + 6.0*3.0))) < 1e-10);
        }

        int main() {
            test_basic_case();
            test_zero_case();
            test_single_element();
            test_self_reference();
            test_varying_mesh_stride();

            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }