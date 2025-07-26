// original code(id = 13): 
 /*
__global__ void resetHeapKernel ( int * heap , int * heapPtr , int numBlock ) { int index = threadIdx . x + blockDim . x * blockIdx . x ; if ( index >= numBlock ) return ; if ( index == 0 ) heapPtr [ 0 ] = numBlock - 1 ; heap [ index ] = numBlock - index - 1 ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void resetHeap(int* heap, int* heapPtr, int numBlock) {
            for (int index = 0; index < numBlock; ++index) {
                if (index == 0) {
                    heapPtr[0] = numBlock - 1;
                }
                heap[index] = numBlock - index - 1;
            }
        }

        int main() {
            // Test case 1: numBlock = 5
            {
                const int numBlock = 5;
                int heap[numBlock];
                int heapPtr[numBlock];
                
                resetHeap(heap, heapPtr, numBlock);
                
                assert(heapPtr[0] == numBlock - 1);
                for (int i = 0; i < numBlock; ++i) {
                    assert(heap[i] == numBlock - i - 1);
                }
            }

            // Test case 2: numBlock = 1
            {
                const int numBlock = 1;
                int heap[numBlock];
                int heapPtr[numBlock];
                
                resetHeap(heap, heapPtr, numBlock);
                
                assert(heapPtr[0] == numBlock - 1);
                for (int i = 0; i < numBlock; ++i) {
                    assert(heap[i] == numBlock - i - 1);
                }
            }

            // Test case 3: numBlock = 0 (edge case)
            {
                const int numBlock = 0;
                int* heap = nullptr;
                int* heapPtr = nullptr;
                
                resetHeap(heap, heapPtr, numBlock);
                // No assertions as function should handle gracefully (no operations performed)
            }

            // Test case 4: numBlock = 10
            {
                const int numBlock = 10;
                int heap[numBlock];
                int heapPtr[numBlock];
                
                resetHeap(heap, heapPtr, numBlock);
                
                assert(heapPtr[0] == numBlock - 1);
                for (int i = 0; i < numBlock; ++i) {
                    assert(heap[i] == numBlock - i - 1);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }