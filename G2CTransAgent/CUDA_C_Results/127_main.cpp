// original code(id = 127): 
 /*
__global__ void Kernel_Transpose2d ( float * dev_transposeArray , float * dev_array , const int r , const int c ) { unsigned int i = blockDim . x * blockIdx . x + threadIdx . x ; unsigned int j = blockDim . y * blockIdx . y + threadIdx . y ; if ( i >= r || j >= c ) return ; int idx_transposeArray , idx_array ; idx_array = i * c + j ; idx_transposeArray = j * r + i ; dev_transposeArray [ idx_transposeArray ] = dev_array [ idx_array ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void Kernel_Transpose2d(float* dev_transposeArray, float* dev_array, const int r, const int c) {
            for (unsigned int i = 0; i < r; ++i) {
                for (unsigned int j = 0; j < c; ++j) {
                    int idx_array = i * c + j;
                    int idx_transposeArray = j * r + i;
                    dev_transposeArray[idx_transposeArray] = dev_array[idx_array];
                }
            }
        }

        void test_Kernel_Transpose2d() {
            // Test case 1: 2x3 matrix
            {
                const int r = 2, c = 3;
                float array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float transposeArray[c * r];
                float expected[c * r] = {1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }

            // Test case 2: 3x2 matrix
            {
                const int r = 3, c = 2;
                float array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float transposeArray[c * r];
                float expected[c * r] = {1.0f, 3.0f, 5.0f, 2.0f, 4.0f, 6.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }

            // Test case 3: 1x1 matrix
            {
                const int r = 1, c = 1;
                float array[r * c] = {42.0f};
                float transposeArray[c * r];
                float expected[c * r] = {42.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }

            // Test case 4: 4x4 matrix (square matrix)
            {
                const int r = 4, c = 4;
                float array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 
                                     5.0f, 6.0f, 7.0f, 8.0f, 
                                     9.0f, 10.0f, 11.0f, 12.0f, 
                                     13.0f, 14.0f, 15.0f, 16.0f};
                float transposeArray[c * r];
                float expected[c * r] = {1.0f, 5.0f, 9.0f, 13.0f, 
                                        2.0f, 6.0f, 10.0f, 14.0f, 
                                        3.0f, 7.0f, 11.0f, 15.0f, 
                                        4.0f, 8.0f, 12.0f, 16.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }

            // Test case 5: 1x5 matrix (single row)
            {
                const int r = 1, c = 5;
                float array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                float transposeArray[c * r];
                float expected[c * r] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }

            // Test case 6: 5x1 matrix (single column)
            {
                const int r = 5, c = 1;
                float array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                float transposeArray[c * r];
                float expected[c * r] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                
                Kernel_Transpose2d(transposeArray, array, r, c);
                
                for (int i = 0; i < c * r; ++i) {
                    assert(transposeArray[i] == expected[i]);
                }
            }
        }

        int main() {
            test_Kernel_Transpose2d();
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }