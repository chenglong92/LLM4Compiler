// original code(id = 60): 
 /*
__global__ void opL12 ( float * vec , float * vec1 , long depth , long rows , long cols ) { unsigned long x = threadIdx . x + blockIdx . x * blockDim . x ; unsigned long y = threadIdx . y + blockIdx . y * blockDim . y ; unsigned long z = threadIdx . z + blockIdx . z * blockDim . z ; unsigned long long i = z * rows * cols + y * cols + x ; unsigned long long j = z * rows * cols + y * cols ; unsigned long size2d = cols ; unsigned long size3d = depth * rows * cols + rows * cols + cols ; if ( x >= cols || y >= rows || z >= depth ) return ; if ( i + cols + 1 >= size3d ) return ; vec [ i + 1 ] = 0.25 * ( vec1 [ i + 1 ] + vec1 [ i ] + vec1 [ i + cols + 1 ] + vec1 [ i + cols ] ) ; if ( j + 1 >= size2d ) return ; vec [ j ] = 0.25 * ( vec1 [ j ] + vec1 [ j + cols ] ) ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void opL12(float* vec, float* vec1, long depth, long rows, long cols) {
            for (long z = 0; z < depth; ++z) {
                for (long y = 0; y < rows; ++y) {
                    for (long x = 0; x < cols; ++x) {
                        unsigned long long i = z * rows * cols + y * cols + x;
                        unsigned long long j = z * rows * cols + y * cols;
                        unsigned long size2d = cols;
                        unsigned long size3d = depth * rows * cols + rows * cols + cols;
                        
                        if (i + cols + 1 < size3d) {
                            vec[i + 1] = 0.25f * (vec1[i + 1] + vec1[i] + vec1[i + cols + 1] + vec1[i + cols]);
                        }
                        
                        if (x == 0 && j + 1 < size2d) {
                            vec[j] = 0.25f * (vec1[j] + vec1[j + cols]);
                        }
                    }
                }
            }
        }

        void test_opL12() {
            // Test case 1: Small 3D array (1x1x1)
            {
                float vec[1] = {0.0f};
                float vec1[1] = {1.0f};
                opL12(vec, vec1, 1, 1, 1);
                assert(vec[0] == 0.0f); // No operation should be performed
            }

            // Test case 2: Small 3D array (1x2x2)
            {
                float vec[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                float vec1[4] = {1.0f, 2.0f, 3.0f, 4.0f};
                opL12(vec, vec1, 1, 2, 2);
                // Check boundary condition (x == 0)
                assert(vec[0] == 0.25f * (vec1[0] + vec1[2]));
                // Check main operation
                assert(vec[1] == 0.25f * (vec1[1] + vec1[0] + vec1[3] + vec1[2]));
            }

            // Test case 3: Medium 3D array (2x2x2)
            {
                float vec[8] = {0.0f};
                float vec1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                opL12(vec, vec1, 2, 2, 2);
                // Check boundary conditions (x == 0)
                assert(vec[0] == 0.25f * (vec1[0] + vec1[2]));
                assert(vec[4] == 0.25f * (vec1[4] + vec1[6]));
                // Check main operations
                assert(vec[1] == 0.25f * (vec1[1] + vec1[0] + vec1[3] + vec1[2]));
                assert(vec[5] == 0.25f * (vec1[5] + vec1[4] + vec1[7] + vec1[6]));
            }

            // Test case 4: Larger 3D array (3x3x3)
            {
                const int size = 27;
                float vec[size] = {0.0f};
                float vec1[size];
                for (int i = 0; i < size; ++i) {
                    vec1[i] = static_cast<float>(i + 1);
                }
                opL12(vec, vec1, 3, 3, 3);
                // Check some boundary conditions (x == 0)
                assert(vec[0] == 0.25f * (vec1[0] + vec1[3]));
                assert(vec[9] == 0.25f * (vec1[9] + vec1[12]));
                // Check some main operations
                assert(vec[1] == 0.25f * (vec1[1] + vec1[0] + vec1[4] + vec1[3]));
                assert(vec[13] == 0.25f * (vec1[13] + vec1[12] + vec1[16] + vec1[15]));
            }
        }

        int main() {
            test_opL12();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }