// original code(id = 18): 
 /*
__global__ void activate_array_leaky_kernel ( float * x , int n ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index < n ) { float val = x [ index ] ; x [ index ] = ( val > 0 ) ? val : val / 10 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void activate_array_leaky(float* x, int n) {
            for (int index = 0; index < n; ++index) {
                float val = x[index];
                x[index] = (val > 0) ? val : val / 10;
            }
        }

        void test_all_positive() {
            float arr[] = {1.5f, 2.0f, 3.5f, 4.0f};
            int n = sizeof(arr) / sizeof(arr[0]);
            float expected[] = {1.5f, 2.0f, 3.5f, 4.0f};
            
            activate_array_leaky(arr, n);
            
            for (int i = 0; i < n; ++i) {
                assert(arr[i] == expected[i]);
            }
            std::cout << "Test all positive passed\n";
        }

        void test_all_negative() {
            float arr[] = {-1.5f, -2.0f, -3.5f, -4.0f};
            int n = sizeof(arr) / sizeof(arr[0]);
            float expected[] = {-0.15f, -0.2f, -0.35f, -0.4f};
            
            activate_array_leaky(arr, n);
            
            for (int i = 0; i < n; ++i) {
                assert(arr[i] == expected[i]);
            }
            std::cout << "Test all negative passed\n";
        }

        void test_mixed_values() {
            float arr[] = {-1.0f, 0.0f, 1.0f, -2.0f, 3.0f};
            int n = sizeof(arr) / sizeof(arr[0]);
            float expected[] = {-0.1f, 0.0f, 1.0f, -0.2f, 3.0f};
            
            activate_array_leaky(arr, n);
            
            for (int i = 0; i < n; ++i) {
                assert(arr[i] == expected[i]);
            }
            std::cout << "Test mixed values passed\n";
        }

        void test_zero_values() {
            float arr[] = {0.0f, 0.0f, 0.0f};
            int n = sizeof(arr) / sizeof(arr[0]);
            float expected[] = {0.0f, 0.0f, 0.0f};
            
            activate_array_leaky(arr, n);
            
            for (int i = 0; i < n; ++i) {
                assert(arr[i] == expected[i]);
            }
            std::cout << "Test zero values passed\n";
        }

        void test_empty_array() {
            float arr[1] = {};  // Empty array (n=0)
            activate_array_leaky(arr, 0);
            std::cout << "Test empty array passed\n";
        }

        int main() {
            test_all_positive();
            test_all_negative();
            test_mixed_values();
            test_zero_values();
            test_empty_array();
            
            std::cout << "All tests passed successfully\n";
            return 0;
        }