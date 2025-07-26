// original code(id = 66): 
 /*
__global__ void matVecRowSubInplaceKernel ( double * mat , const double * vec , int m , int n ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index < m * n ) { int i = index / n ; int j = index % n ; mat [ i * n + j ] -= vec [ j ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void matVecRowSubInplace(double* mat, const double* vec, int m, int n);

        void test_matVecRowSubInplace() {
            // Test case 1: 2x3 matrix and 3-element vector
            {
                double mat[] = {1.0, 2.0, 3.0,
                                4.0, 5.0, 6.0};
                double vec[] = {1.0, 2.0, 3.0};
                int m = 2;
                int n = 3;
                double expected[] = {0.0, 0.0, 0.0,
                                    3.0, 3.0, 3.0};
                
                matVecRowSubInplace(mat, vec, m, n);
                
                for (int i = 0; i < m * n; ++i) {
                    assert(mat[i] == expected[i]);
                }
            }
            
            // Test case 2: 1x1 matrix and 1-element vector
            {
                double mat[] = {5.0};
                double vec[] = {2.0};
                int m = 1;
                int n = 1;
                double expected[] = {3.0};
                
                matVecRowSubInplace(mat, vec, m, n);
                
                assert(mat[0] == expected[0]);
            }
            
            // Test case 3: 3x2 matrix and 2-element vector (non-square)
            {
                double mat[] = {1.5, 2.5,
                                3.5, 4.5,
                                5.5, 6.5};
                double vec[] = {0.5, 1.5};
                int m = 3;
                int n = 2;
                double expected[] = {1.0, 1.0,
                                    3.0, 3.0,
                                    5.0, 5.0};
                
                matVecRowSubInplace(mat, vec, m, n);
                
                for (int i = 0; i < m * n; ++i) {
                    assert(mat[i] == expected[i]);
                }
            }
            
            // Test case 4: Empty matrix and vector (edge case)
            {
                double mat[] = {};
                double vec[] = {};
                int m = 0;
                int n = 0;
                
                matVecRowSubInplace(mat, vec, m, n);
                // No assertion needed, just checking it doesn't crash
            }
            
            // Test case 5: Large matrix (4x4) and vector
            {
                double mat[] = {10.0, 20.0, 30.0, 40.0,
                                50.0, 60.0, 70.0, 80.0,
                                90.0, 100.0, 110.0, 120.0,
                                130.0, 140.0, 150.0, 160.0};
                double vec[] = {5.0, 10.0, 15.0, 20.0};
                int m = 4;
                int n = 4;
                double expected[] = {5.0, 10.0, 15.0, 20.0,
                                    45.0, 50.0, 55.0, 60.0,
                                    85.0, 90.0, 95.0, 100.0,
                                    125.0, 130.0, 135.0, 140.0};
                
                matVecRowSubInplace(mat, vec, m, n);
                
                for (int i = 0; i < m * n; ++i) {
                    assert(mat[i] == expected[i]);
                }
            }
            
            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_matVecRowSubInplace();
            return 0;
        }