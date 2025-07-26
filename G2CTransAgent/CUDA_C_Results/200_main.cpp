// original code(id = 200): 
 /*
__global__ void vadd ( const float * a , const float * b , float * c , const unsigned int count ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i < count ) { c [ i ] = a [ i ] + b [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <limits>

void vadd(const float* a, const float* b, float* c, const unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    // Test case 1: Basic addition
    {
        const unsigned int count = 3;
        float a[count] = {1.0f, 2.0f, 3.0f};
        float b[count] = {4.0f, 5.0f, 6.0f};
        float c[count] = {0.0f};
        
        vadd(a, b, c, count);
        
        assert(c[0] == 5.0f);
        assert(c[1] == 7.0f);
        assert(c[2] == 9.0f);
    }

    // Test case 2: Addition with zero
    {
        const unsigned int count = 4;
        float a[count] = {0.0f, 0.0f, 0.0f, 0.0f};
        float b[count] = {1.0f, 2.0f, 3.0f, 4.0f};
        float c[count] = {0.0f};
        
        vadd(a, b, c, count);
        
        assert(c[0] == 1.0f);
        assert(c[1] == 2.0f);
        assert(c[2] == 3.0f);
        assert(c[3] == 4.0f);
    }

    // Test case 3: Addition with negative numbers
    {
        const unsigned int count = 3;
        float a[count] = {-1.0f, -2.0f, -3.0f};
        float b[count] = {4.0f, 5.0f, 6.0f};
        float c[count] = {0.0f};
        
        vadd(a, b, c, count);
        
        assert(c[0] == 3.0f);
        assert(c[1] == 3.0f);
        assert(c[2] == 3.0f);
    }

    // Test case 4: Addition with maximum float values
    {
        const unsigned int count = 2;
        float a[count] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
        float b[count] = {std::numeric_limits<float>::max(), -std::numeric_limits<float>::max()};
        float c[count] = {0.0f};
        
        vadd(a, b, c, count);
        
        assert(c[0] == std::numeric_limits<float>::infinity());
        assert(c[1] == 0.0f);
    }

    // Test case 5: Empty arrays (count = 0)
    {
        const unsigned int count = 0;
        float a[1] = {1.0f};
        float b[1] = {2.0f};
        float c[1] = {0.0f};
        
        vadd(a, b, c, count);
        
        // No assertions needed as the function should handle count=0 without issues
    }

    // Test case 6: Addition with very small numbers (denormalized)
    {
        const unsigned int count = 2;
        float a[count] = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
        float b[count] = {std::numeric_limits<float>::min(), -std::numeric_limits<float>::min()};
        float c[count] = {0.0f};
        
        vadd(a, b, c, count);
        
        assert(c[0] == 2 * std::numeric_limits<float>::min());
        assert(c[1] == 0.0f);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}