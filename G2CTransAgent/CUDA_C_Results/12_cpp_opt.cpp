// Optimized code(id = 12): 

void resetHeap(int* heap, int* heapPtr, int numBlock) {
    for (int index = 0; index < numBlock; ++index) {
        if (index == 0) {
            heapPtr[0] = numBlock - 1;
        }
        heap[index] = numBlock - index - 1;
    }
}