// original code(id = 89): 
 /*
__global__ void sum_array_1Dgrid_1Dblock ( float * a , float * b , float * c , int nx ) { int gid = blockDim . x * blockIdx . x + threadIdx . x ; c [ gid ] = a [ gid ] + b [ gid ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void sum_array_1Dgrid_1Dblock(float* a, float* b, float* c, int nx) {
    for (int gid = 0; gid < nx; ++gid) {
        c[gid] = a[gid] + b[gid];
    }
}

void test_sum_array_basic() {
    const int nx = 5;
    float a[nx] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float b[nx] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    float c[nx] = {0.0f};

    sum_array_1Dgrid_1Dblock(a, b, c, nx);

    for (int i = 0; i < nx; ++i) {
        assert(c[i] == a[i] + b[i]);
    }
}

void test_sum_array_empty() {
    const int nx = 0;
    float* a = nullptr;
    float* b = nullptr;
    float* c = nullptr;

    sum_array_1Dgrid_1Dblock(a, b, c, nx);
    // No operation should be performed, just checking it doesn't crash
}

void test_sum_array_single_element() {
    const int nx = 1;
    float a[nx] = {10.0f};
    float b[nx] = {20.0f};
    float c[nx] = {0.0f};

    sum_array_1Dgrid_1Dblock(a, b, c, nx);

    assert(c[0] == 30.0f);
}

void test_sum_array_negative_values() {
    const int nx = 4;
    float a[nx] = {-1.0f, -2.0f, -3.0f, -4.0f};
    float b[nx] = {1.0f, 2.0f, 3.0f, 4.0f};
    float c[nx] = {0.0f};

    sum_array_1Dgrid_1Dblock(a, b, c, nx);

    for (int i = 0; i < nx; ++i) {
        assert(c[i] == 0.0f);
    }
}

void test_sum_array_large_size() {
    const int nx = 1000;
    float* a = new float[nx];
    float* b = new float[nx];
    float* c = new float[nx];

    for (int i = 0; i < nx; ++i) {
        a[i] = static_cast<float>(i);
        b[i] = static_cast<float>(i * 2);
        c[i] = 0.0f;
    }

    sum_array_1Dgrid_1Dblock(a, b, c, nx);

    for (int i = 0; i < nx; ++i) {
        assert(c[i] == a[i] + b[i]);
    }

    delete[] a;
    delete[] b;
    delete[] c;
}

int main() {
    test_sum_array_basic();
    test_sum_array_empty();
    test_sum_array_single_element();
    test_sum_array_negative_values();
    test_sum_array_large_size();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}