// original code(id = 209): 
 /*
__global__ void add_matrix ( float * a , float * b , float * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] + b [ idx ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void add_matrix(float* a, float* b, float* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] + b[idx];
    }
}

void test_add_matrix() {
    // Test case 1: Small matrices
    {
        const int N = 3;
        float a[N] = {1.0f, 2.0f, 3.0f};
        float b[N] = {4.0f, 5.0f, 6.0f};
        float c[N];
        float expected[N] = {5.0f, 7.0f, 9.0f};
        
        add_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Empty matrix
    {
        const int N = 0;
        float* a = nullptr;
        float* b = nullptr;
        float* c = nullptr;
        
        add_matrix(a, b, c, N); // Should not crash
    }

    // Test case 3: Large matrix
    {
        const int N = 1000;
        float a[N];
        float b[N];
        float c[N];
        float expected[N];
        
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<float>(i);
            b[i] = static_cast<float>(i * 2);
            expected[i] = a[i] + b[i];
        }
        
        add_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Negative values
    {
        const int N = 4;
        float a[N] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float b[N] = {1.0f, 2.0f, 3.0f, 4.0f};
        float c[N];
        float expected[N] = {0.0f, 0.0f, 0.0f, 0.0f};
        
        add_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: Floating point values
    {
        const int N = 5;
        float a[N] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
        float b[N] = {0.9f, 0.8f, 0.7f, 0.6f, 0.5f};
        float c[N];
        float expected[N] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        
        add_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }
}

int main() {
    test_add_matrix();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}