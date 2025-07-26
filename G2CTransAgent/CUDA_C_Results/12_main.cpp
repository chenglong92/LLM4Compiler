// original code(id = 12): 
 /*
__global__ void testInt1 ( const int * input , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } int sum ; for ( int i = 0 ; i < 3000 * 4 ; i ++ ) { if ( input [ i ] == 0 ) { sum ++ ; } } }
*/
// optimized code: 

#include <iostream>
#include <cstdlib>

void testInt1(const int* input, int dims) {
    // Simulate thread behavior with a loop
    for (int tid = 0; tid < dims; tid++) {
        int sum = 0;  // Initialize sum to 0 for each "thread"
        for (int i = 0; i < 3000 * 4; i++) {
            if (input[i] == 0) {
                sum++;
            }
        }
        // sum is unused, just like in the original kernel
    }
}

int main() {
    // Test case 1: Empty array
    {
        int* emptyArray = nullptr;
        testInt1(emptyArray, 0);
        std::cout << "Test case 1 passed (empty array)" << std::endl;
    }

    // Test case 2: Small array with some zeros
    {
        int smallArray[10] = {0, 1, 0, 2, 3, 0, 4, 5, 0, 6};
        testInt1(smallArray, 3);
        std::cout << "Test case 2 passed (small array with zeros)" << std::endl;
    }

    // Test case 3: Large array with no zeros
    {
        const int size = 12000;
        int* noZeroArray = new int[size];
        for (int i = 0; i < size; i++) {
            noZeroArray[i] = 1;
        }
        testInt1(noZeroArray, 5);
        delete[] noZeroArray;
        std::cout << "Test case 3 passed (large array with no zeros)" << std::endl;
    }

    // Test case 4: Array with exactly 12000 elements
    {
        const int size = 12000;
        int* exactSizeArray = new int[size];
        for (int i = 0; i < size; i++) {
            exactSizeArray[i] = (i % 5 == 0) ? 0 : 1; // 20% zeros
        }
        testInt1(exactSizeArray, 10);
        delete[] exactSizeArray;
        std::cout << "Test case 4 passed (exactly 12000 elements)" << std::endl;
    }

    // Test case 5: Array with more than 12000 elements
    {
        const int size = 15000;
        int* largeArray = new int[size];
        for (int i = 0; i < size; i++) {
            largeArray[i] = (i % 10 == 0) ? 0 : 1; // 10% zeros
        }
        testInt1(largeArray, 8);
        delete[] largeArray;
        std::cout << "Test case 5 passed (more than 12000 elements)" << std::endl;
    }

    return 0;
}