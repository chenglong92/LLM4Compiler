// original code(id = 130): 
 /*
__global__ void memcpy_kernel ( int * dst , int * src , size_t n ) { int num = gridDim . x * blockDim . x ; int id = blockDim . x * blockIdx . x + threadIdx . x ; for ( int i = id ; i < n / sizeof ( int ) ; i += num ) { dst [ i ] = src [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cstring>
#include <cassert>

void memcpy_kernel(int* dst, int* src, size_t n) {
    size_t num_elements = n / sizeof(int);
    for (size_t i = 0; i < num_elements; ++i) {
        dst[i] = src[i];
    }
}

int main() {
    // Test case 1: Normal case with multiple elements
    int src1[] = {1, 2, 3, 4, 5};
    int dst1[5] = {0};
    memcpy_kernel(dst1, src1, sizeof(src1));
    for (int i = 0; i < 5; ++i) {
        assert(dst1[i] == src1[i]);
    }

    // Test case 2: Single element
    int src2 = 42;
    int dst2 = 0;
    memcpy_kernel(&dst2, &src2, sizeof(src2));
    assert(dst2 == src2);

    // Test case 3: Empty data (n = 0)
    int src3[] = {1, 2, 3};
    int dst3[3] = {0};
    memcpy_kernel(dst3, src3, 0);
    for (int i = 0; i < 3; ++i) {
        assert(dst3[i] == 0);
    }

    // Test case 4: Partial copy (n not multiple of sizeof(int))
    int src4[] = {10, 20, 30, 40};
    int dst4[4] = {0};
    memcpy_kernel(dst4, src4, sizeof(int) * 2 + 1); // Should copy 2 elements
    assert(dst4[0] == 10);
    assert(dst4[1] == 20);
    assert(dst4[2] == 0);
    assert(dst4[3] == 0);

    // Test case 5: Large array
    const size_t large_size = 1000;
    int* src5 = new int[large_size];
    int* dst5 = new int[large_size]();
    for (size_t i = 0; i < large_size; ++i) {
        src5[i] = static_cast<int>(i);
    }
    memcpy_kernel(dst5, src5, large_size * sizeof(int));
    for (size_t i = 0; i < large_size; ++i) {
        assert(dst5[i] == src5[i]);
    }
    delete[] src5;
    delete[] dst5;

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}