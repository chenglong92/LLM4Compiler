// original code(id = 92): 
 /*
__global__ void add ( int n , float * x , float * y ) { int i = threadIdx . x ; if ( i < n ) y [ i ] = x [ i ] + y [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void add(int n, float* x, float* y) {
    for (int i = 0; i < n; ++i) {
        y[i] = x[i] + y[i];
    }
}

int main() {
    // Test case 1: Simple addition with positive numbers
    {
        float x[] = {1.0f, 2.0f, 3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float expected[] = {5.0f, 7.0f, 9.0f};
        add(3, x, y);
        for (int i = 0; i < 3; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 2: Addition with negative numbers
    {
        float x[] = {-1.0f, -2.0f, -3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float expected[] = {3.0f, 3.0f, 3.0f};
        add(3, x, y);
        for (int i = 0; i < 3; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 3: Addition with zero
    {
        float x[] = {0.0f, 0.0f, 0.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float expected[] = {4.0f, 5.0f, 6.0f};
        add(3, x, y);
        for (int i = 0; i < 3; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    // Test case 4: Empty arrays (n = 0)
    {
        float x[] = {1.0f, 2.0f, 3.0f};
        float y[] = {4.0f, 5.0f, 6.0f};
        float original_y[] = {4.0f, 5.0f, 6.0f};
        add(0, x, y);
        for (int i = 0; i < 3; ++i) {
            assert(y[i] == original_y[i]);
        }
    }

    // Test case 5: Single element arrays
    {
        float x[] = {1.5f};
        float y[] = {2.5f};
        float expected[] = {4.0f};
        add(1, x, y);
        assert(y[0] == expected[0]);
    }

    // Test case 6: Large arrays
    {
        const int size = 1000;
        float x[size];
        float y[size];
        float expected[size];
        for (int i = 0; i < size; ++i) {
            x[i] = static_cast<float>(i);
            y[i] = static_cast<float>(i * 2);
            expected[i] = x[i] + y[i];
        }
        add(size, x, y);
        for (int i = 0; i < size; ++i) {
            assert(y[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}