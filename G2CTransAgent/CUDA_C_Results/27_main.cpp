// original code(id = 27): 
 /*
__global__ void add_100 ( int numElements , int * data ) { if ( blockIdx . x < numElements ) { data [ blockIdx . x ] += 100 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void add_100(int numElements, int* data) {
    for (int i = 0; i < numElements; ++i) {
        data[i] += 100;
    }
}

void test_add_100() {
    // Test case 1: Normal case with multiple elements
    {
        int data[] = {1, 2, 3, 4, 5};
        int expected[] = {101, 102, 103, 104, 105};
        add_100(5, data);
        for (int i = 0; i < 5; ++i) {
            assert(data[i] == expected[i]);
        }
    }

    // Test case 2: Single element
    {
        int data[] = {42};
        int expected[] = {142};
        add_100(1, data);
        assert(data[0] == expected[0]);
    }

    // Test case 3: Empty array (should do nothing)
    {
        int* data = nullptr;
        add_100(0, data);
        // No assertion needed as it shouldn't crash
    }

    // Test case 4: Negative numbers
    {
        int data[] = {-10, -20, -30};
        int expected[] = {90, 80, 70};
        add_100(3, data);
        for (int i = 0; i < 3; ++i) {
            assert(data[i] == expected[i]);
        }
    }

    // Test case 5: Large numbers
    {
        int data[] = {2147483647, -2147483648};
        int expected[] = {-2147483549, -2147483548};
        add_100(2, data);
        for (int i = 0; i < 2; ++i) {
            assert(data[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_add_100();
    return 0;
}