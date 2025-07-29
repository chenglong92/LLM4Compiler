// original code(id = 13): 
 /*
__global__ void resetHeapKernel ( int * heap , int * heapPtr , int numBlock ) { int index = threadIdx . x + blockDim . x * blockIdx . x ; if ( index >= numBlock ) return ; if ( index == 0 ) heapPtr [ 0 ] = numBlock - 1 ; heap [ index ] = numBlock - index - 1 ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void resetHeap(int* heap, int* heapPtr, int numBlock);

        void testResetHeap() {
            // Test case 1: Normal case with 5 blocks
            {
                int heap[5];
                int heapPtr[1];
                resetHeap(heap, heapPtr, 5);
                
                assert(heapPtr[0] == 4);
                assert(heap[0] == 4);
                assert(heap[1] == 3);
                assert(heap[2] == 2);
                assert(heap[3] == 1);
                assert(heap[4] == 0);
            }

            // Test case 2: Single block case
            {
                int heap[1];
                int heapPtr[1];
                resetHeap(heap, heapPtr, 1);
                
                assert(heapPtr[0] == 0);
                assert(heap[0] == 0);
            }

            // Test case 3: Empty case (0 blocks)
            {
                int* heap = nullptr;
                int heapPtr[1];
                resetHeap(heap, heapPtr, 0);
                
                // No heap elements to check, just verify heapPtr is set
                // Note: The function doesn't actually set heapPtr[0] when numBlock is 0
                // This might be a potential issue in the function
            }

            // Test case 4: Larger number of blocks
            {
                const int num = 10;
                int heap[num];
                int heapPtr[1];
                resetHeap(heap, heapPtr, num);
                
                assert(heapPtr[0] == num - 1);
                for (int i = 0; i < num; ++i) {
                    assert(heap[i] == num - i - 1);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            testResetHeap();
            return 0;
        }

        void resetHeap(int* heap, int* heapPtr, int numBlock) {
            for (int index = 0; index < numBlock; ++index) {
                if (index == 0) {
                    heapPtr[0] = numBlock - 1;
                }
                heap[index] = numBlock - index - 1;
            }
        }