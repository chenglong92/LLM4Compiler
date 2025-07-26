// original code(id = 115): 
 /*
__global__ void mathKernel1 ( float * c ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; float ia , ib ; ia = ib = 0.0f ; if ( tid % 2 == 0 ) { ia = 100.0f ; } else { ib = 200.0f ; } c [ tid ] = ia + ib ; }
*/
// optimized code: 

#include <iostream>
#include <vector>
#include <cassert>

void mathKernel1(float* c, int num_elements) {
    for (int tid = 0; tid < num_elements; ++tid) {
        float ia = 0.0f, ib = 0.0f;
        if (tid % 2 == 0) {
            ia = 100.0f;
        } else {
            ib = 200.0f;
        }
        c[tid] = ia + ib;
    }
}

int main() {
    // Test case 1: Even number of elements (covers both branches)
    {
        const int num_elements = 4;
        float c[num_elements];
        mathKernel1(c, num_elements);
        
        assert(c[0] == 100.0f);  // tid=0 (even)
        assert(c[1] == 200.0f);  // tid=1 (odd)
        assert(c[2] == 100.0f);  // tid=2 (even)
        assert(c[3] == 200.0f);  // tid=3 (odd)
    }

    // Test case 2: Odd number of elements (covers both branches)
    {
        const int num_elements = 5;
        float c[num_elements];
        mathKernel1(c, num_elements);
        
        assert(c[0] == 100.0f);  // tid=0 (even)
        assert(c[1] == 200.0f);  // tid=1 (odd)
        assert(c[2] == 100.0f);  // tid=2 (even)
        assert(c[3] == 200.0f);  // tid=3 (odd)
        assert(c[4] == 100.0f);  // tid=4 (even)
    }

    // Test case 3: Single element (even tid)
    {
        const int num_elements = 1;
        float c[num_elements];
        mathKernel1(c, num_elements);
        
        assert(c[0] == 100.0f);  // tid=0 (even)
    }

    // Test case 4: Empty array (should do nothing)
    {
        const int num_elements = 0;
        float c[1] = {0.0f};  // Dummy array
        mathKernel1(c, num_elements);
        
        // No assertions needed, just shouldn't crash
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}