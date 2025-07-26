// original code(id = 117): 
 /*
__global__ void add_vec_scalaire_gpu ( int * vec , int * res , int a , long N ) { long i = ( long ) blockIdx . x * ( long ) blockDim . x + ( long ) threadIdx . x ; if ( i < N ) { res [ i ] = vec [ i ] + a ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void add_vec_scalaire_cpu(int* vec, int* res, int a, long N) {
    for (long i = 0; i < N; ++i) {
        res[i] = vec[i] + a;
    }
}

void test_add_vec_scalaire_cpu() {
    // Test case 1: Basic functionality
    {
        int vec[] = {1, 2, 3, 4, 5};
        int res[5];
        int a = 10;
        long N = 5;
        add_vec_scalaire_cpu(vec, res, a, N);
        for (long i = 0; i < N; ++i) {
            assert(res[i] == vec[i] + a);
        }
    }

    // Test case 2: Negative scalar
    {
        int vec[] = {10, 20, 30, 40, 50};
        int res[5];
        int a = -5;
        long N = 5;
        add_vec_scalaire_cpu(vec, res, a, N);
        for (long i = 0; i < N; ++i) {
            assert(res[i] == vec[i] + a);
        }
    }

    // Test case 3: Zero scalar
    {
        int vec[] = {100, 200, 300, 400, 500};
        int res[5];
        int a = 0;
        long N = 5;
        add_vec_scalaire_cpu(vec, res, a, N);
        for (long i = 0; i < N; ++i) {
            assert(res[i] == vec[i] + a);
        }
    }

    // Test case 4: Empty vector
    {
        int* vec = nullptr;
        int* res = nullptr;
        int a = 10;
        long N = 0;
        add_vec_scalaire_cpu(vec, res, a, N);
        // No assertion needed as it should not crash
    }

    // Test case 5: Large vector
    {
        const long N = 1000000;
        int* vec = new int[N];
        int* res = new int[N];
        int a = 7;
        for (long i = 0; i < N; ++i) {
            vec[i] = i;
        }
        add_vec_scalaire_cpu(vec, res, a, N);
        for (long i = 0; i < N; ++i) {
            assert(res[i] == vec[i] + a);
        }
        delete[] vec;
        delete[] res;
    }

    // Test case 6: Negative vector elements
    {
        int vec[] = {-1, -2, -3, -4, -5};
        int res[5];
        int a = 3;
        long N = 5;
        add_vec_scalaire_cpu(vec, res, a, N);
        for (long i = 0; i < N; ++i) {
            assert(res[i] == vec[i] + a);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_add_vec_scalaire_cpu();
    return 0;
}