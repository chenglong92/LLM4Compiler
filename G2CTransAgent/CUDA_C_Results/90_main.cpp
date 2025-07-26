// original code(id = 90): 
 /*
__global__ void scale_dev ( float * array , float scale , int N ) { int idx = blockIdx . x * blockDim . x + threadIdx . x ; if ( idx < N ) { array [ idx ] *= scale ; } return ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void scale_dev(float* array, float scale, int N) {
    for (int idx = 0; idx < N; ++idx) {
        array[idx] *= scale;
    }
}

void test_scale_dev_normal_case() {
    float array[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float scale = 2.0f;
    int N = 4;
    scale_dev(array, scale, N);
    assert(array[0] == 2.0f);
    assert(array[1] == 4.0f);
    assert(array[2] == 6.0f);
    assert(array[3] == 8.0f);
}

void test_scale_dev_edge_case_zero_scale() {
    float array[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float scale = 0.0f;
    int N = 4;
    scale_dev(array, scale, N);
    assert(array[0] == 0.0f);
    assert(array[1] == 0.0f);
    assert(array[2] == 0.0f);
    assert(array[3] == 0.0f);
}

void test_scale_dev_edge_case_negative_scale() {
    float array[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float scale = -1.0f;
    int N = 4;
    scale_dev(array, scale, N);
    assert(array[0] == -1.0f);
    assert(array[1] == -2.0f);
    assert(array[2] == -3.0f);
    assert(array[3] == -4.0f);
}

void test_scale_dev_edge_case_empty_array() {
    float array[] = {};
    float scale = 2.0f;
    int N = 0;
    scale_dev(array, scale, N);
    // No assertion needed as function should handle N=0 without issues
}

void test_scale_dev_error_case_null_pointer() {
    float* array = nullptr;
    float scale = 2.0f;
    int N = 4;
    // This should ideally be handled by the function, but currently it's not
    // For now, we expect it to crash or behave unpredictably
    scale_dev(array, scale, N);
}

int main() {
    test_scale_dev_normal_case();
    test_scale_dev_edge_case_zero_scale();
    test_scale_dev_edge_case_negative_scale();
    test_scale_dev_edge_case_empty_array();
    // Uncomment the line below to test the error case (expecting a crash)
    // test_scale_dev_error_case_null_pointer();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}