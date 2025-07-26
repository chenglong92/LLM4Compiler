// original code(id = 158): 
 /*
__global__ void allExp2InplaceKernel ( double * arr , int n ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { arr [ i ] = arr [ i ] * 9 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void allExp2Inplace(double* arr, int n) {
            for (int i = 0; i < n; ++i) {
                arr[i] = arr[i] * 9;
            }
        }

        int main() {
            // Test case 1: Basic test with positive numbers
            double arr1[] = {1.0, 2.0, 3.0};
            int size1 = sizeof(arr1) / sizeof(arr1[0]);
            allExp2Inplace(arr1, size1);
            assert(arr1[0] == 9.0);
            assert(arr1[1] == 18.0);
            assert(arr1[2] == 27.0);

            // Test case 2: Test with negative numbers
            double arr2[] = {-1.0, -2.0, -3.0};
            int size2 = sizeof(arr2) / sizeof(arr2[0]);
            allExp2Inplace(arr2, size2);
            assert(arr2[0] == -9.0);
            assert(arr2[1] == -18.0);
            assert(arr2[2] == -27.0);

            // Test case 3: Test with zero
            double arr3[] = {0.0, 0.0, 0.0};
            int size3 = sizeof(arr3) / sizeof(arr3[0]);
            allExp2Inplace(arr3, size3);
            assert(arr3[0] == 0.0);
            assert(arr3[1] == 0.0);
            assert(arr3[2] == 0.0);

            // Test case 4: Test with mixed positive, negative, and zero values
            double arr4[] = {1.5, -2.5, 0.0};
            int size4 = sizeof(arr4) / sizeof(arr4[0]);
            allExp2Inplace(arr4, size4);
            assert(arr4[0] == 13.5);
            assert(arr4[1] == -22.5);
            assert(arr4[2] == 0.0);

            // Test case 5: Test with single element
            double arr5[] = {10.0};
            int size5 = sizeof(arr5) / sizeof(arr5[0]);
            allExp2Inplace(arr5, size5);
            assert(arr5[0] == 90.0);

            // Test case 6: Test with empty array (should not crash)
            double arr6[] = {};
            int size6 = sizeof(arr6) / sizeof(arr6[0]);
            allExp2Inplace(arr6, size6);

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }