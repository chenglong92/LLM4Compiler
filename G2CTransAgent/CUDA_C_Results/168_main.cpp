// original code(id = 168): 
 /*
__global__ void multMat ( int n , int * arrForce_d , int * arrDistance_d , int * arrAnswer_d ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < n ) { arrAnswer_d [ i ] = arrForce_d [ i ] * arrDistance_d [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void multMat(int n, int* arrForce_d, int* arrDistance_d, int* arrAnswer_d) {
    for (int i = 0; i < n; ++i) {
        arrAnswer_d[i] = arrForce_d[i] * arrDistance_d[i];
    }
}

void test_multMat() {
    // Test case 1: Basic multiplication
    {
        int n = 3;
        int arrForce_d[] = {1, 2, 3};
        int arrDistance_d[] = {4, 5, 6};
        int arrAnswer_d[3];
        int expected[] = {4, 10, 18};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        for (int i = 0; i < n; ++i) {
            assert(arrAnswer_d[i] == expected[i]);
        }
    }

    // Test case 2: Zero values
    {
        int n = 3;
        int arrForce_d[] = {0, 0, 0};
        int arrDistance_d[] = {4, 5, 6};
        int arrAnswer_d[3];
        int expected[] = {0, 0, 0};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        for (int i = 0; i < n; ++i) {
            assert(arrAnswer_d[i] == expected[i]);
        }
    }

    // Test case 3: Negative values
    {
        int n = 3;
        int arrForce_d[] = {-1, -2, -3};
        int arrDistance_d[] = {4, 5, 6};
        int arrAnswer_d[3];
        int expected[] = {-4, -10, -18};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        for (int i = 0; i < n; ++i) {
            assert(arrAnswer_d[i] == expected[i]);
        }
    }

    // Test case 4: Mixed positive and negative values
    {
        int n = 4;
        int arrForce_d[] = {1, -2, 3, -4};
        int arrDistance_d[] = {-5, 6, -7, 8};
        int arrAnswer_d[4];
        int expected[] = {-5, -12, -21, -32};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        for (int i = 0; i < n; ++i) {
            assert(arrAnswer_d[i] == expected[i]);
        }
    }

    // Test case 5: Single element
    {
        int n = 1;
        int arrForce_d[] = {10};
        int arrDistance_d[] = {20};
        int arrAnswer_d[1];
        int expected[] = {200};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        assert(arrAnswer_d[0] == expected[0]);
    }

    // Test case 6: Large values
    {
        int n = 2;
        int arrForce_d[] = {1000000, 2000000};
        int arrDistance_d[] = {3000000, 4000000};
        int arrAnswer_d[2];
        int expected[] = {3000000000000, 8000000000000};

        multMat(n, arrForce_d, arrDistance_d, arrAnswer_d);

        for (int i = 0; i < n; ++i) {
            assert(arrAnswer_d[i] == expected[i]);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_multMat();
    return 0;
}