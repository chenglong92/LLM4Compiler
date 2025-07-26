// original code(id = 110): 
 /*
__global__ void shiftIndices ( long * vec_out , const long by , const long imageSize , const long N ) { long idx = threadIdx . x + blockDim . x * blockIdx . x ; if ( idx < N ) { vec_out [ idx ] = ( imageSize + ( ( idx - N / 2 + by ) % imageSize ) ) % imageSize ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void shiftIndices(long* vec_out, const long by, const long imageSize, const long N) {
            for (long idx = 0; idx < N; ++idx) {
                vec_out[idx] = (imageSize + ((idx - N / 2 + by) % imageSize)) % imageSize;
            }
        }

        void printArray(long* arr, long size) {
            for (long i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        void test_shiftIndices() {
            // Test case 1: Basic test with small values
            {
                const long N = 5;
                const long imageSize = 10;
                const long by = 2;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {7, 8, 9, 0, 1};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 2: Negative shift
            {
                const long N = 5;
                const long imageSize = 10;
                const long by = -3;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {2, 3, 4, 5, 6};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 3: Large shift (larger than imageSize)
            {
                const long N = 5;
                const long imageSize = 10;
                const long by = 15;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {0, 1, 2, 3, 4};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 4: Negative shift larger than imageSize
            {
                const long N = 5;
                const long imageSize = 10;
                const long by = -13;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {2, 3, 4, 5, 6};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 5: Even number of elements
            {
                const long N = 6;
                const long imageSize = 10;
                const long by = 1;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {8, 9, 0, 1, 2, 3};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 6: imageSize smaller than N
            {
                const long N = 10;
                const long imageSize = 5;
                const long by = 1;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {1, 2, 3, 4, 0, 1, 2, 3, 4, 0};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            // Test case 7: Zero shift
            {
                const long N = 5;
                const long imageSize = 10;
                const long by = 0;
                long vec_out[N];
                
                shiftIndices(vec_out, by, imageSize, N);
                
                long expected[N] = {5, 6, 7, 8, 9};
                for (long i = 0; i < N; ++i) {
                    assert(vec_out[i] == expected[i]);
                }
            }

            std::cout << "All tests passed successfully!" << std::endl;
        }

        int main() {
            test_shiftIndices();
            return 0;
        }