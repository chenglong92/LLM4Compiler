// original code(id = 161): 
 /*
__global__ void dadd_matrix ( double * a , double * b , double * c , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) c [ idx ] = a [ idx ] + b [ idx ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void dadd_matrix(double* a, double* b, double* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] + b[idx];
    }
}

int main() {
    // Test case 1: Small array
    {
        const int N = 3;
        double a[N] = {1.0, 2.0, 3.0};
        double b[N] = {4.0, 5.0, 6.0};
        double c[N];
        double expected[N] = {5.0, 7.0, 9.0};
        
        dadd_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 2: Empty array (edge case)
    {
        const int N = 0;
        double* a = nullptr;
        double* b = nullptr;
        double* c = nullptr;
        
        dadd_matrix(a, b, c, N); // Should handle without crashing
    }

    // Test case 3: Large array
    {
        const int N = 1000;
        double a[N];
        double b[N];
        double c[N];
        double expected[N];
        
        for (int i = 0; i < N; ++i) {
            a[i] = i * 1.5;
            b[i] = i * 2.5;
            expected[i] = a[i] + b[i];
        }
        
        dadd_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 4: Negative values
    {
        const int N = 5;
        double a[N] = {-1.0, -2.0, -3.0, -4.0, -5.0};
        double b[N] = {1.0, 2.0, 3.0, 4.0, 5.0};
        double c[N];
        double expected[N] = {0.0, 0.0, 0.0, 0.0, 0.0};
        
        dadd_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    // Test case 5: Mixed positive and negative values
    {
        const int N = 4;
        double a[N] = {-1.5, 2.3, -3.7, 4.2};
        double b[N] = {1.5, -2.3, 3.7, -4.2};
        double c[N];
        double expected[N] = {0.0, 0.0, 0.0, 0.0};
        
        dadd_matrix(a, b, c, N);
        
        for (int i = 0; i < N; ++i) {
            assert(c[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}