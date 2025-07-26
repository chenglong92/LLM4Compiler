// original code(id = 114): 
 /*
__global__ void pythagoras ( unsigned char * a , unsigned char * b , unsigned char * c ) { int idx = ( blockIdx . x * blockDim . x ) + threadIdx . x ; float af = float ( a [ idx ] ) ; float bf = float ( b [ idx ] ) ; c [ idx ] = ( unsigned char ) sqrtf ( af * af + bf * bf ) ; }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void pythagoras(unsigned char* a, unsigned char* b, unsigned char* c, int size) {
    for (int idx = 0; idx < size; ++idx) {
        float af = float(a[idx]);
        float bf = float(b[idx]);
        c[idx] = static_cast<unsigned char>(sqrtf(af * af + bf * bf));
    }
}

void test_pythagoras() {
    // Test case 1: Simple case with small values
    {
        unsigned char a[] = {3, 5, 6};
        unsigned char b[] = {4, 12, 8};
        unsigned char c[3];
        unsigned char expected[] = {5, 13, 10};
        
        pythagoras(a, b, c, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Edge case with zero values
    {
        unsigned char a[] = {0, 0, 0};
        unsigned char b[] = {0, 0, 0};
        unsigned char c[3];
        unsigned char expected[] = {0, 0, 0};
        
        pythagoras(a, b, c, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 3: Maximum unsigned char values (255)
    {
        unsigned char a[] = {255};
        unsigned char b[] = {255};
        unsigned char c[1];
        unsigned char expected[] = {static_cast<unsigned char>(sqrtf(255 * 255 + 255 * 255))};
        
        pythagoras(a, b, c, 1);
        
        assert(c[0] == expected[0]);
    }

    // Test case 4: Mixed values including zero
    {
        unsigned char a[] = {0, 9, 16};
        unsigned char b[] = {0, 12, 12};
        unsigned char c[3];
        unsigned char expected[] = {0, 15, 20};
        
        pythagoras(a, b, c, 3);
        
        for (int i = 0; i < 3; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: Single element array
    {
        unsigned char a[] = {7};
        unsigned char b[] = {24};
        unsigned char c[1];
        unsigned char expected[] = {25};
        
        pythagoras(a, b, c, 1);
        
        assert(c[0] == expected[0]);
    }

    // Test case 6: Large array
    {
        const int size = 1000;
        unsigned char a[size];
        unsigned char b[size];
        unsigned char c[size];
        
        for (int i = 0; i < size; ++i) {
            a[i] = i % 256;
            b[i] = (i + 1) % 256;
        }
        
        pythagoras(a, b, c, size);
        
        for (int i = 0; i < size; ++i) {
            float af = float(a[i]);
            float bf = float(b[i]);
            unsigned char expected = static_cast<unsigned char>(sqrtf(af * af + bf * bf));
            assert(c[i] == expected);
        }
    }
}

int main() {
    test_pythagoras();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}