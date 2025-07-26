// original code(id = 99): 
 /*
__global__ void evenoddincrement ( float * g_data , int even_inc , int odd_inc ) { int tx = threadIdx . x + blockIdx . x * blockDim . x ; if ( ( tx % 2 ) == 0 ) { g_data [ tx ] += even_inc ; } else { g_data [ tx ] += odd_inc ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void evenoddincrement(float* g_data, int size, int even_inc, int odd_inc) {
    for (int tx = 0; tx < size; ++tx) {
        if ((tx % 2) == 0) {
            g_data[tx] += even_inc;
        } else {
            g_data[tx] += odd_inc;
        }
    }
}

int main() {
    // Test case 1: Even and odd increments with positive values
    {
        float data[] = {1.0f, 2.0f, 3.0f, 4.0f};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, 5, 10);
        assert(data[0] == 6.0f);
        assert(data[1] == 12.0f);
        assert(data[2] == 8.0f);
        assert(data[3] == 14.0f);
    }

    // Test case 2: Even and odd increments with negative values
    {
        float data[] = {10.0f, 20.0f, 30.0f, 40.0f};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, -5, -10);
        assert(data[0] == 5.0f);
        assert(data[1] == 10.0f);
        assert(data[2] == 25.0f);
        assert(data[3] == 30.0f);
    }

    // Test case 3: Zero increments
    {
        float data[] = {1.5f, 2.5f, 3.5f, 4.5f};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, 0, 0);
        assert(data[0] == 1.5f);
        assert(data[1] == 2.5f);
        assert(data[2] == 3.5f);
        assert(data[3] == 4.5f);
    }

    // Test case 4: Single element array (even index)
    {
        float data[] = {100.0f};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, 1, 2);
        assert(data[0] == 101.0f);
    }

    // Test case 5: Single element array (odd index - though size 1 can't have odd index)
    // This case is to show the function still works with size 1
    {
        float data[] = {100.0f};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, 0, 5);
        assert(data[0] == 100.0f); // Still even index (0), so odd_inc not applied
    }

    // Test case 6: Empty array
    {
        float data[] = {};
        int size = sizeof(data) / sizeof(data[0]);
        evenoddincrement(data, size, 1, 2);
        // No assertions needed, just checking it doesn't crash
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}