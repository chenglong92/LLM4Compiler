// original code(id = 116): 
 /*
__global__ void Kernel_Avg ( float * dev_arrayMax , float * dev_array , const int r , const int c ) { unsigned int tid = blockDim . x * blockIdx . x + threadIdx . x ; int N = r ; float sum ; int i ; while ( tid < N ) { i = tid ; sum = 0.0 ; for ( int j = 0 ; j < c ; j ++ ) { sum += dev_array [ i * c + j ] ; } dev_arrayMax [ i ] = sum / c ; tid += gridDim . x * blockDim . x ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

void Kernel_Avg(float* dev_arrayMax, float* dev_array, const int r, const int c);

void test_Kernel_Avg() {
    // Test case 1: Basic test with small matrix
    {
        const int r = 2;
        const int c = 3;
        float dev_array[r * c] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
        float dev_arrayMax[r];
        float expected[r] = {2.0f, 5.0f};

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        for (int i = 0; i < r; ++i) {
            assert(dev_arrayMax[i] == expected[i]);
        }
    }

    // Test case 2: Single row matrix
    {
        const int r = 1;
        const int c = 4;
        float dev_array[r * c] = {10.0f, 20.0f, 30.0f, 40.0f};
        float dev_arrayMax[r];
        float expected[r] = {25.0f};

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        assert(dev_arrayMax[0] == expected[0]);
    }

    // Test case 3: Single column matrix
    {
        const int r = 3;
        const int c = 1;
        float dev_array[r * c] = {5.0f, 10.0f, 15.0f};
        float dev_arrayMax[r];
        float expected[r] = {5.0f, 10.0f, 15.0f};

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        for (int i = 0; i < r; ++i) {
            assert(dev_arrayMax[i] == expected[i]);
        }
    }

    // Test case 4: Large matrix with random values
    {
        const int r = 100;
        const int c = 100;
        float dev_array[r * c];
        float dev_arrayMax[r];
        float expected[r];

        srand(time(nullptr));
        for (int i = 0; i < r; ++i) {
            float sum = 0.0f;
            for (int j = 0; j < c; ++j) {
                dev_array[i * c + j] = static_cast<float>(rand() % 1000) / 10.0f;
                sum += dev_array[i * c + j];
            }
            expected[i] = sum / c;
        }

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        for (int i = 0; i < r; ++i) {
            assert(std::abs(dev_arrayMax[i] - expected[i]) < 1e-5f);
        }
    }

    // Test case 5: Empty matrix (should handle gracefully)
    {
        const int r = 0;
        const int c = 0;
        float* dev_array = nullptr;
        float* dev_arrayMax = nullptr;

        Kernel_Avg(dev_arrayMax, dev_array, r, c);
        // No assertion as function should just return without error
    }

    // Test case 6: Matrix with negative values
    {
        const int r = 2;
        const int c = 2;
        float dev_array[r * c] = {-1.0f, -2.0f, -3.0f, -4.0f};
        float dev_arrayMax[r];
        float expected[r] = {-1.5f, -3.5f};

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        for (int i = 0; i < r; ++i) {
            assert(dev_arrayMax[i] == expected[i]);
        }
    }

    // Test case 7: Matrix with mixed positive and negative values
    {
        const int r = 2;
        const int c = 3;
        float dev_array[r * c] = {-1.0f, 2.0f, -3.0f, 4.0f, -5.0f, 6.0f};
        float dev_arrayMax[r];
        float expected[r] = {-0.6666667f, 1.6666667f};

        Kernel_Avg(dev_arrayMax, dev_array, r, c);

        for (int i = 0; i < r; ++i) {
            assert(std::abs(dev_arrayMax[i] - expected[i]) < 1e-5f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_Kernel_Avg();
    return 0;
}