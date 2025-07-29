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

        int main() {
            // Test case 1: Swap arrays of size 3
            {
                float arr1[] = {1.0f, 2.0f, 3.0f};
                float arr2[] = {4.0f, 5.0f, 6.0f};
                const int size = 3;
                
                copy_swap(arr1, arr2, size);
                
                assert(arr1[0] == 4.0f && arr1[1] == 5.0f && arr1[2] == 6.0f);
                assert(arr2[0] == 1.0f && arr2[1] == 2.0f && arr2[2] == 3.0f);
            }

            // Test case 2: Swap empty arrays
            {
                float arr1[] = {};
                float arr2[] = {};
                const int size = 0;
                
                copy_swap(arr1, arr2, size);
                
                // No elements to verify, just ensure no crash
            }

            // Test case 3: Swap single-element arrays
            {
                float arr1[] = {10.5f};
                float arr2[] = {20.5f};
                const int size = 1;
                
                copy_swap(arr1, arr2, size);
                
                assert(arr1[0] == 20.5f);
                assert(arr2[0] == 10.5f);
            }

            // Test case 4: Swap arrays with negative and positive values
            {
                float arr1[] = {-1.0f, -2.0f, -3.0f};
                float arr2[] = {1.0f, 2.0f, 3.0f};
                const int size = 3;
                
                copy_swap(arr1, arr2, size);
                
                assert(arr1[0] == 1.0f && arr1[1] == 2.0f && arr1[2] == 3.0f);
                assert(arr2[0] == -1.0f && arr2[1] == -2.0f && arr2[2] == -3.0f);
            }

            // Test case 5: Swap large arrays
            {
                const int size = 1000;
                float arr1[size];
                float arr2[size];
                
                for (int i = 0; i < size; ++i) {
                    arr1[i] = static_cast<float>(i);
                    arr2[i] = static_cast<float>(size - i);
                }
                
                copy_swap(arr1, arr2, size);
                
                for (int i = 0; i < size; ++i) {
                    assert(arr1[i] == static_cast<float>(size - i));
                    assert(arr2[i] == static_cast<float>(i));
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }