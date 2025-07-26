// original code(id = 154): 
 /*
__global__ void incrementArrayOnDevice ( float * a , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) a [ idx ] = a [ idx ] + 1.f ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void incrementArrayOnDevice(float* a, int N) {
            for (int idx = 0; idx < N; ++idx) {
                a[idx] = a[idx] + 1.0f;
            }
        }

        void testIncrementArrayOnDevice() {
            // Test case 1: Normal case with multiple elements
            {
                float arr[] = {1.0f, 2.0f, 3.0f, 4.0f};
                int N = sizeof(arr) / sizeof(arr[0]);
                incrementArrayOnDevice(arr, N);
                assert(arr[0] == 2.0f);
                assert(arr[1] == 3.0f);
                assert(arr[2] == 4.0f);
                assert(arr[3] == 5.0f);
            }

            // Test case 2: Boundary case with single element
            {
                float arr[] = {0.0f};
                int N = sizeof(arr) / sizeof(arr[0]);
                incrementArrayOnDevice(arr, N);
                assert(arr[0] == 1.0f);
            }

            // Test case 3: Boundary case with empty array (N=0)
            {
                float arr[] = {1.0f, 2.0f, 3.0f};
                int N = 0;
                incrementArrayOnDevice(arr, N);
                // Should not modify the array when N=0
                assert(arr[0] == 1.0f);
                assert(arr[1] == 2.0f);
                assert(arr[2] == 3.0f);
            }

            // Test case 4: Negative N (should be handled safely)
            {
                float arr[] = {1.0f, 2.0f, 3.0f};
                int N = -1;
                incrementArrayOnDevice(arr, N);
                // Should not modify the array when N is negative
                assert(arr[0] == 1.0f);
                assert(arr[1] == 2.0f);
                assert(arr[2] == 3.0f);
            }

            // Test case 5: Large array
            {
                const int LARGE_SIZE = 10000;
                float* largeArr = new float[LARGE_SIZE];
                for (int i = 0; i < LARGE_SIZE; ++i) {
                    largeArr[i] = static_cast<float>(i);
                }
                incrementArrayOnDevice(largeArr, LARGE_SIZE);
                for (int i = 0; i < LARGE_SIZE; ++i) {
                    assert(largeArr[i] == static_cast<float>(i) + 1.0f);
                }
                delete[] largeArr;
            }
        }

        int main() {
            testIncrementArrayOnDevice();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }