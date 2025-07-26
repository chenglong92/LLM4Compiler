// original code(id = 126): 
 /*
__global__ void opL21 ( float * vec , float * vec1 , long depth , long rows , long cols ) { unsigned long x = threadIdx . x + blockIdx . x * blockDim . x ; unsigned long y = threadIdx . y + blockIdx . y * blockDim . y ; unsigned long z = threadIdx . z + blockIdx . z * blockDim . z ; unsigned long long i = z * rows * cols + y * cols + x ; unsigned long long j = z * rows * cols + x ; unsigned long size2d = cols ; unsigned long size3d = depth * rows * cols + rows * cols + cols ; if ( x >= cols || y >= rows || z >= depth ) return ; if ( i + cols + 1 >= size3d ) return ; vec [ i + cols ] = 0.25 * ( vec1 [ i + 1 ] + vec1 [ i ] + vec1 [ i + cols + 1 ] + vec1 [ i + cols ] ) ; if ( j + 1 >= size2d ) return ; vec [ j ] = ( vec1 [ j ] + vec1 [ j + 1 ] ) / 4 ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void opL21(float* vec, float* vec1, long depth, long rows, long cols);

        int main() {
            // Test case 1: Minimum dimensions (1x1x1)
            {
                float vec[1] = {0};
                float vec1[1] = {1.0f};
                opL21(vec, vec1, 1, 1, 1);
                assert(vec[0] == 0.0f); // Neither condition applies
            }

            // Test case 2: 1x2x2 - tests 2D condition only
            {
                float vec[4] = {0};
                float vec1[4] = {1.0f, 2.0f, 3.0f, 4.0f};
                opL21(vec, vec1, 1, 2, 2);
                // Check 2D condition results
                assert(vec[0] == (1.0f + 2.0f)/4.0f);
                assert(vec[1] == (2.0f + 1.0f)/4.0f); // Wraps around?
                // 3D condition doesn't apply for last element
                assert(vec[3] == 0.0f);
            }

            // Test case 3: 2x2x2 - tests both conditions
            {
                float vec[8] = {0};
                float vec1[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                opL21(vec, vec1, 2, 2, 2);
                // Check some 3D condition results
                assert(vec[2] == 0.25f * (vec1[3] + vec1[2] + vec1[5] + vec1[4]));
                // Check some 2D condition results
                assert(vec[0] == (vec1[0] + vec1[1])/4.0f);
                assert(vec[4] == (vec1[4] + vec1[5])/4.0f);
            }

            // Test case 4: 1x3x3 - tests boundary conditions
            {
                float vec[9] = {0};
                float vec1[9] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
                opL21(vec, vec1, 1, 3, 3);
                // Check 3D condition for middle element
                assert(vec[4] == 0.25f * (vec1[5] + vec1[4] + vec1[8] + vec1[7]));
                // Check 2D condition for first element
                assert(vec[0] == (vec1[0] + vec1[1])/4.0f);
                // Last element should be unchanged (conditions don't apply)
                assert(vec[8] == 0.0f);
            }

            // Test case 5: 3x1x1 - tests depth with minimal rows/cols
            {
                float vec[3] = {0};
                float vec1[3] = {1.0f, 2.0f, 3.0f};
                opL21(vec, vec1, 3, 1, 1);
                // Only 2D condition might apply
                assert(vec[0] == (vec1[0] + vec1[1])/4.0f);
                assert(vec[1] == (vec1[1] + vec1[2])/4.0f);
                assert(vec[2] == 0.0f); // No next element
            }

            std::cout << "All tests passed!" << std::endl;
            return 0;
        }

        void opL21(float* vec, float* vec1, long depth, long rows, long cols) {
            for (unsigned long z = 0; z < depth; ++z) {
                for (unsigned long y = 0; y < rows; ++y) {
                    for (unsigned long x = 0; x < cols; ++x) {
                        unsigned long long i = z * rows * cols + y * cols + x;
                        unsigned long long j = z * rows * cols + x;
                        unsigned long size2d = cols;
                        unsigned long size3d = depth * rows * cols + rows * cols + cols;
                        
                        if (i + cols + 1 < size3d) {
                            vec[i + cols] = 0.25f * (vec1[i + 1] + vec1[i] + vec1[i + cols + 1] + vec1[i + cols]);
                        }
                        
                        if (j + 1 < size2d) {
                            vec[j] = (vec1[j] + vec1[j + 1]) / 4.0f;
                        }
                    }
                }
            }
        }