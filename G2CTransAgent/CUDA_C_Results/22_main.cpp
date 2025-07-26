// original code(id = 22): 
 /*
__global__ void zeroIndices ( long * vec_out , const long N ) { int idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx < N ) { vec_out [ idx ] = vec_out [ idx ] - vec_out [ 0 ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void zeroIndices(long* vec_out, const long N);

        int main() {
            // Test case 1: Normal case with positive numbers
            {
                long arr1[] = {5, 10, 15, 20};
                const long N1 = sizeof(arr1)/sizeof(arr1[0]);
                long expected1[] = {0, 5, 10, 15};
                zeroIndices(arr1, N1);
                for (long i = 0; i < N1; ++i) {
                    assert(arr1[i] == expected1[i]);
                }
            }

            // Test case 2: Normal case with negative numbers
            {
                long arr2[] = {-3, -1, 2, 5};
                const long N2 = sizeof(arr2)/sizeof(arr2[0]);
                long expected2[] = {0, 2, 5, 8};
                zeroIndices(arr2, N2);
                for (long i = 0; i < N2; ++i) {
                    assert(arr2[i] == expected2[i]);
                }
            }

            // Test case 3: All elements are the same
            {
                long arr3[] = {7, 7, 7, 7, 7};
                const long N3 = sizeof(arr3)/sizeof(arr3[0]);
                long expected3[] = {0, 0, 0, 0, 0};
                zeroIndices(arr3, N3);
                for (long i = 0; i < N3; ++i) {
                    assert(arr3[i] == expected3[i]);
                }
            }

            // Test case 4: Edge case with N=1
            {
                long arr4[] = {42};
                const long N4 = sizeof(arr4)/sizeof(arr4[0]);
                long expected4[] = {0};
                zeroIndices(arr4, N4);
                assert(arr4[0] == expected4[0]);
            }

            // Test case 5: Edge case with N=0 (should do nothing)
            {
                long arr5[] = {1, 2, 3};
                const long N5 = 0;
                zeroIndices(arr5, N5);
                // Verify array remains unchanged
                assert(arr5[0] == 1);
                assert(arr5[1] == 2);
                assert(arr5[2] == 3);
            }

            // Test case 6: First element is zero
            {
                long arr6[] = {0, 10, 20, 30};
                const long N6 = sizeof(arr6)/sizeof(arr6[0]);
                long expected6[] = {0, 10, 20, 30};
                zeroIndices(arr6, N6);
                for (long i = 0; i < N6; ++i) {
                    assert(arr6[i] == expected6[i]);
                }
            }

            // Test case 7: Large values
            {
                long arr7[] = {10000000000, 10000000001, 10000000002};
                const long N7 = sizeof(arr7)/sizeof(arr7[0]);
                long expected7[] = {0, 1, 2};
                zeroIndices(arr7, N7);
                for (long i = 0; i < N7; ++i) {
                    assert(arr7[i] == expected7[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void zeroIndices(long* vec_out, const long N) {
            for (long idx = 0; idx < N; ++idx) {
                vec_out[idx] = vec_out[idx] - vec_out[0];
            }
        }