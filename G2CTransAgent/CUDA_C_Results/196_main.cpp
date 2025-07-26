// original code(id = 196): 
 /*
__global__ void matVecRowSubKernel ( const double * mat , const double * vec , double * buf , int m , int n ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index < m * n ) { int i = index / n ; int j = index % n ; buf [ i * n + j ] = mat [ i * n + j ] - vec [ j ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matVecRowSub(const double* mat, const double* vec, double* buf, int m, int n) {
            for (int index = 0; index < m * n; ++index) {
                int i = index / n;
                int j = index % n;
                buf[i * n + j] = mat[i * n + j] - vec[j];
            }
        }

        void printMatrix(const double* mat, int m, int n) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    std::cout << mat[i * n + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        bool compareMatrices(const double* a, const double* b, int m, int n) {
            for (int i = 0; i < m * n; ++i) {
                if (std::abs(a[i] - b[i]) > 1e-9) {
                    return false;
                }
            }
            return true;
        }

        void test_matVecRowSub() {
            // Test case 1: Small matrix and vector
            {
                double mat[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0}; // 2x3 matrix
                double vec[] = {0.5, 1.0, 1.5}; // 3-element vector
                double buf[6];
                double expected[] = {0.5, 1.0, 1.5, 3.5, 4.0, 4.5};
                
                matVecRowSub(mat, vec, buf, 2, 3);
                assert(compareMatrices(buf, expected, 2, 3));
            }

            // Test case 2: Single row matrix
            {
                double mat[] = {10.0, 20.0, 30.0}; // 1x3 matrix
                double vec[] = {5.0, 10.0, 15.0}; // 3-element vector
                double buf[3];
                double expected[] = {5.0, 10.0, 15.0};
                
                matVecRowSub(mat, vec, buf, 1, 3);
                assert(compareMatrices(buf, expected, 1, 3));
            }

            // Test case 3: Square matrix
            {
                double mat[] = {1.0, 2.0, 3.0, 4.0}; // 2x2 matrix
                double vec[] = {0.1, 0.2}; // 2-element vector
                double buf[4];
                double expected[] = {0.9, 1.8, 3.9, 3.8};
                
                matVecRowSub(mat, vec, buf, 2, 2);
                assert(compareMatrices(buf, expected, 2, 2));
            }

            // Test case 4: Negative values
            {
                double mat[] = {-1.0, -2.0, -3.0, -4.0}; // 2x2 matrix
                double vec[] = {0.5, -1.5}; // 2-element vector
                double buf[4];
                double expected[] = {-1.5, -0.5, -3.5, -2.5};
                
                matVecRowSub(mat, vec, buf, 2, 2);
                assert(compareMatrices(buf, expected, 2, 2));
            }

            // Test case 5: Large matrix
            {
                const int m = 100;
                const int n = 50;
                double mat[m * n];
                double vec[n];
                double buf[m * n];
                double expected[m * n];
                
                for (int i = 0; i < m * n; ++i) {
                    mat[i] = i + 1;
                }
                for (int j = 0; j < n; ++j) {
                    vec[j] = j + 1;
                }
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        expected[i * n + j] = mat[i * n + j] - vec[j];
                    }
                }
                
                matVecRowSub(mat, vec, buf, m, n);
                assert(compareMatrices(buf, expected, m, n));
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_matVecRowSub();
            return 0;
        }