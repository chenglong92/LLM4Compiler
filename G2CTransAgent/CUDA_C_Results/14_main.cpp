// original code(id = 14): 
 /*
__global__ void copy_swap ( float * f_in , float * f_target , const int L_x ) { const int k_x = threadIdx . x + blockIdx . x * blockDim . x ; if ( k_x >= L_x ) { return ; } float tempval = 0.f ; tempval = f_in [ k_x ] ; f_in [ k_x ] = f_target [ k_x ] ; f_target [ k_x ] = tempval ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void copy_swap(float* f_in, float* f_target, const int L_x) {
            for (int k_x = 0; k_x < L_x; ++k_x) {
                float tempval = f_in[k_x];
                f_in[k_x] = f_target[k_x];
                f_target[k_x] = tempval;
            }
        }

        void print_array(float* arr, int size) {
            for (int i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        bool arrays_equal(float* a, float* b, int size) {
            for (int i = 0; i < size; ++i) {
                if (a[i] != b[i]) {
                    return false;
                }
            }
            return true;
        }

        void test_copy_swap() {
            // Test case 1: Normal case with multiple elements
            {
                float arr1[] = {1.1f, 2.2f, 3.3f};
                float arr2[] = {4.4f, 5.5f, 6.6f};
                float expected1[] = {4.4f, 5.5f, 6.6f};
                float expected2[] = {1.1f, 2.2f, 3.3f};
                const int size = 3;
                
                copy_swap(arr1, arr2, size);
                
                assert(arrays_equal(arr1, expected1, size));
                assert(arrays_equal(arr2, expected2, size));
            }

            // Test case 2: Empty arrays (L_x = 0)
            {
                float arr1[] = {1.0f, 2.0f};
                float arr2[] = {3.0f, 4.0f};
                float original1[] = {1.0f, 2.0f};
                float original2[] = {3.0f, 4.0f};
                const int size = 0;
                
                copy_swap(arr1, arr2, size);
                
                assert(arrays_equal(arr1, original1, 2));
                assert(arrays_equal(arr2, original2, 2));
            }

            // Test case 3: Single element arrays
            {
                float arr1[] = {10.5f};
                float arr2[] = {20.5f};
                float expected1[] = {20.5f};
                float expected2[] = {10.5f};
                const int size = 1;
                
                copy_swap(arr1, arr2, size);
                
                assert(arrays_equal(arr1, expected1, size));
                assert(arrays_equal(arr2, expected2, size));
            }

            // Test case 4: Arrays with same values
            {
                float arr1[] = {5.0f, 5.0f};
                float arr2[] = {5.0f, 5.0f};
                float expected1[] = {5.0f, 5.0f};
                float expected2[] = {5.0f, 5.0f};
                const int size = 2;
                
                copy_swap(arr1, arr2, size);
                
                assert(arrays_equal(arr1, expected1, size));
                assert(arrays_equal(arr2, expected2, size));
            }

            // Test case 5: Partial swap (L_x less than array size)
            {
                float arr1[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float arr2[] = {5.0f, 6.0f, 7.0f, 8.0f};
                float expected1[] = {5.0f, 6.0f, 3.0f, 4.0f};
                float expected2[] = {1.0f, 2.0f, 7.0f, 8.0f};
                const int size = 2;
                
                copy_swap(arr1, arr2, size);
                
                assert(arrays_equal(arr1, expected1, 4));
                assert(arrays_equal(arr2, expected2, 4));
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_copy_swap();
            return 0;
        }