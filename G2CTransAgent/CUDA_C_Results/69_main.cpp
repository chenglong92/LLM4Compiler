// original code(id = 69): 
 /*
__global__ void transposeNaive ( int * vector , int * transposed , int size ) { int column = threadIdx . x + blockDim . x * blockIdx . x ; int row = threadIdx . y + blockDim . x * blockIdx . y ; if ( row < size && column < size ) transposed [ row + column * size ] = vector [ column + row * size ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void transposeNaive(int* vector, int* transposed, int size) {
            for (int row = 0; row < size; ++row) {
                for (int column = 0; column < size; ++column) {
                    transposed[row + column * size] = vector[column + row * size];
                }
            }
        }

        void printMatrix(int* matrix, int size) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << matrix[i * size + j] << " ";
                }
                std::cout << std::endl;
            }
        }

        bool areMatricesEqual(int* a, int* b, int size) {
            for (int i = 0; i < size * size; ++i) {
                if (a[i] != b[i]) {
                    return false;
                }
            }
            return true;
        }

        void testTransposeNaive() {
            // Test case 1: 2x2 matrix
            {
                int size = 2;
                int input[] = {1, 2, 3, 4};
                int expected[] = {1, 3, 2, 4};
                int output[4];
                
                transposeNaive(input, output, size);
                assert(areMatricesEqual(output, expected, size));
            }

            // Test case 2: 3x3 matrix
            {
                int size = 3;
                int input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                int expected[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
                int output[9];
                
                transposeNaive(input, output, size);
                assert(areMatricesEqual(output, expected, size));
            }

            // Test case 3: 1x1 matrix
            {
                int size = 1;
                int input[] = {42};
                int expected[] = {42};
                int output[1];
                
                transposeNaive(input, output, size);
                assert(areMatricesEqual(output, expected, size));
            }

            // Test case 4: size 0 (shouldn't crash)
            {
                int size = 0;
                int* input = nullptr;
                int* output = nullptr;
                
                transposeNaive(input, output, size);
                // No assertion as we're just checking it doesn't crash
            }

            // Test case 5: negative size (shouldn't crash, though behavior is undefined)
            {
                int size = -1;
                int input[] = {1};
                int output[1];
                
                transposeNaive(input, output, size);
                // No assertion as we're just checking it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            testTransposeNaive();
            return 0;
        }