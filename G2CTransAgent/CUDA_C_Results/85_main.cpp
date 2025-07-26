// original code(id = 85): 
 /*
__global__ void gather_points_kernel ( int b , int c , int n , int m , const float * __restrict__ points , const int * __restrict__ idx , float * __restrict__ out ) { for ( int i = blockIdx . x ; i < b ; i += gridDim . x ) { for ( int l = blockIdx . y ; l < c ; l += gridDim . y ) { for ( int j = threadIdx . x ; j < m ; j += blockDim . x ) { int a = idx [ i * m + j ] ; out [ ( i * c + l ) * m + j ] = points [ ( i * c + l ) * n + a ] ; } } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void gather_points_kernel(int b, int c, int n, int m, const float* points, const int* idx, float* out) {
            for (int i = 0; i < b; ++i) {
                for (int l = 0; l < c; ++l) {
                    for (int j = 0; j < m; ++j) {
                        int a = idx[i * m + j];
                        out[(i * c + l) * m + j] = points[(i * c + l) * n + a];
                    }
                }
            }
        }

        void test_normal_case() {
            const int b = 2, c = 3, n = 5, m = 4;
            float points[b * c * n] = {
                1.1, 1.2, 1.3, 1.4, 1.5,
                1.6, 1.7, 1.8, 1.9, 2.0,
                2.1, 2.2, 2.3, 2.4, 2.5,
                2.6, 2.7, 2.8, 2.9, 3.0,
                3.1, 3.2, 3.3, 3.4, 3.5,
                3.6, 3.7, 3.8, 3.9, 4.0
            };
            int idx[b * m] = {0, 2, 4, 1, 1, 3, 0, 2};
            float out[b * c * m] = {0};

            gather_points_kernel(b, c, n, m, points, idx, out);

            // Verify the results
            float expected[b * c * m] = {
                1.1, 1.3, 1.5, 1.2,
                1.6, 1.8, 2.0, 1.7,
                2.1, 2.3, 2.5, 2.2,
                2.7, 2.9, 2.6, 2.8,
                3.2, 3.4, 3.1, 3.3,
                3.7, 3.9, 3.6, 3.8
            };

            for (int i = 0; i < b * c * m; ++i) {
                assert(out[i] == expected[i]);
            }

            std::cout << "Normal case test passed!\n";
        }

        void test_edge_case_single_element() {
            const int b = 1, c = 1, n = 1, m = 1;
            float points[b * c * n] = {42.0};
            int idx[b * m] = {0};
            float out[b * c * m] = {0};

            gather_points_kernel(b, c, n, m, points, idx, out);

            assert(out[0] == 42.0);
            std::cout << "Edge case (single element) test passed!\n";
        }

        void test_edge_case_empty_output() {
            const int b = 1, c = 1, n = 5, m = 0;
            float points[b * c * n] = {1.0, 2.0, 3.0, 4.0, 5.0};
            int idx[b * m] = {};
            float out[b * c * m] = {};

            gather_points_kernel(b, c, n, m, points, idx, out);

            // Should not crash
            std::cout << "Edge case (empty output) test passed!\n";
        }

        void test_invalid_case_negative_index() {
            const int b = 1, c = 1, n = 3, m = 2;
            float points[b * c * n] = {1.0, 2.0, 3.0};
            int idx[b * m] = {-1, 2};
            float out[b * c * m] = {0};

            try {
                gather_points_kernel(b, c, n, m, points, idx, out);
                std::cerr << "Invalid case (negative index) test failed - no exception thrown!\n";
            } catch (...) {
                std::cout << "Invalid case (negative index) test passed (caught exception)!\n";
            }
        }

        void test_invalid_case_out_of_bound_index() {
            const int b = 1, c = 1, n = 3, m = 2;
            float points[b * c * n] = {1.0, 2.0, 3.0};
            int idx[b * m] = {0, 3};
            float out[b * c * m] = {0};

            try {
                gather_points_kernel(b, c, n, m, points, idx, out);
                std::cerr << "Invalid case (out of bound index) test failed - no exception thrown!\n";
            } catch (...) {
                std::cout << "Invalid case (out of bound index) test passed (caught exception)!\n";
            }
        }

        void test_random_case() {
            std::srand(std::time(0));
            const int b = 3, c = 2, n = 10, m = 5;
            float points[b * c * n];
            int idx[b * m];
            float out[b * c * m] = {0};

            // Initialize random points
            for (int i = 0; i < b * c * n; ++i) {
                points[i] = static_cast<float>(std::rand()) / RAND_MAX * 100.0f;
            }

            // Initialize random indices (valid range)
            for (int i = 0; i < b * m; ++i) {
                idx[i] = std::rand() % n;
            }

            gather_points_kernel(b, c, n, m, points, idx, out);

            // Verify random results
            for (int i = 0; i < b; ++i) {
                for (int l = 0; l < c; ++l) {
                    for (int j = 0; j < m; ++j) {
                        int a = idx[i * m + j];
                        float expected = points[(i * c + l) * n + a];
                        float actual = out[(i * c + l) * m + j];
                        assert(actual == expected);
                    }
                }
            }

            std::cout << "Random case test passed!\n";
        }

        int main() {
            test_normal_case();
            test_edge_case_single_element();
            test_edge_case_empty_output();
            test_invalid_case_negative_index();
            test_invalid_case_out_of_bound_index();
            test_random_case();

            return 0;
        }