// original code(id = 120): 
 /*
__global__ void kernelIsFirst ( int * head , int * first_pts , int n ) { int i = threadIdx . x + blockDim . x * blockIdx . x ; if ( i < n ) { if ( head [ i ] == 1 ) first_pts [ i ] = i ; else first_pts [ i ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void kernelIsFirst(int* head, int* first_pts, int n) {
    for (int i = 0; i < n; ++i) {
        if (head[i] == 1) {
            first_pts[i] = i;
        } else {
            first_pts[i] = 0;
        }
    }
}

void test_kernelIsFirst() {
    // Test case 1: All elements are 1
    {
        int head[] = {1, 1, 1, 1};
        int first_pts[4];
        int expected[] = {0, 1, 2, 3};
        kernelIsFirst(head, first_pts, 4);
        for (int i = 0; i < 4; ++i) {
            assert(first_pts[i] == expected[i]);
        }
    }

    // Test case 2: No elements are 1
    {
        int head[] = {0, 2, 3, 4};
        int first_pts[4];
        int expected[] = {0, 0, 0, 0};
        kernelIsFirst(head, first_pts, 4);
        for (int i = 0; i < 4; ++i) {
            assert(first_pts[i] == expected[i]);
        }
    }

    // Test case 3: Mixed elements (some 1s, some not)
    {
        int head[] = {1, 0, 1, 0, 1};
        int first_pts[5];
        int expected[] = {0, 0, 2, 0, 4};
        kernelIsFirst(head, first_pts, 5);
        for (int i = 0; i < 5; ++i) {
            assert(first_pts[i] == expected[i]);
        }
    }

    // Test case 4: Single element array (1)
    {
        int head[] = {1};
        int first_pts[1];
        int expected[] = {0};
        kernelIsFirst(head, first_pts, 1);
        assert(first_pts[0] == expected[0]);
    }

    // Test case 5: Single element array (not 1)
    {
        int head[] = {2};
        int first_pts[1];
        int expected[] = {0};
        kernelIsFirst(head, first_pts, 1);
        assert(first_pts[0] == expected[0]);
    }

    // Test case 6: Empty array
    {
        int* head = nullptr;
        int* first_pts = nullptr;
        kernelIsFirst(head, first_pts, 0);
        // No assertions needed as it shouldn't crash
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_kernelIsFirst();
    return 0;
}