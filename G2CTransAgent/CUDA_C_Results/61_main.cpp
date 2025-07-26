// original code(id = 61): 
 /*
__global__ void intMultiply ( int * result , const int * val1 , const int val2 , const unsigned int size ) { int i = threadIdx . x + blockIdx . x * blockDim . x ; if ( i < size ) { result [ blockIdx . x ] = val1 [ blockIdx . x ] * val2 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void intMultiply(int* result, const int* val1, const int val2, const unsigned int size) {
    for (unsigned int i = 0; i < size; ++i) {
        result[i] = val1[i] * val2;
    }
}

void testIntMultiply() {
    // Test case 1: Multiply positive numbers
    {
        const unsigned int size = 3;
        int val1[size] = {1, 2, 3};
        int val2 = 4;
        int result[size];
        
        intMultiply(result, val1, val2, size);
        
        assert(result[0] == 4);
        assert(result[1] == 8);
        assert(result[2] == 12);
    }
    
    // Test case 2: Multiply with zero
    {
        const unsigned int size = 3;
        int val1[size] = {1, 2, 3};
        int val2 = 0;
        int result[size];
        
        intMultiply(result, val1, val2, size);
        
        assert(result[0] == 0);
        assert(result[1] == 0);
        assert(result[2] == 0);
    }
    
    // Test case 3: Multiply negative numbers
    {
        const unsigned int size = 3;
        int val1[size] = {-1, -2, -3};
        int val2 = -4;
        int result[size];
        
        intMultiply(result, val1, val2, size);
        
        assert(result[0] == 4);
        assert(result[1] == 8);
        assert(result[2] == 12);
    }
    
    // Test case 4: Multiply mixed positive and negative numbers
    {
        const unsigned int size = 3;
        int val1[size] = {-1, 2, -3};
        int val2 = 5;
        int result[size];
        
        intMultiply(result, val1, val2, size);
        
        assert(result[0] == -5);
        assert(result[1] == 10);
        assert(result[2] == -15);
    }
    
    // Test case 5: Multiply with size zero (edge case)
    {
        const unsigned int size = 0;
        int val1[1] = {1}; // Dummy array, won't be accessed
        int val2 = 5;
        int result[1]; // Dummy array, won't be accessed
        
        intMultiply(result, val1, val2, size);
        // No assertions, just checking it doesn't crash
    }
    
    // Test case 6: Multiply large numbers
    {
        const unsigned int size = 3;
        int val1[size] = {1000000, 2000000, 3000000};
        int val2 = 2;
        int result[size];
        
        intMultiply(result, val1, val2, size);
        
        assert(result[0] == 2000000);
        assert(result[1] == 4000000);
        assert(result[2] == 6000000);
    }
    
    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testIntMultiply();
    return 0;
}