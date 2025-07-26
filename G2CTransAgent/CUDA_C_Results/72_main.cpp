// original code(id = 72): 
 /*
__global__ void iKernel ( float * A , float * B , float * C , const int N ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i < N ) C [ i ] = A [ i ] + B [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <vector>
#include <cassert>

void iKernel(float* A, float* B, float* C, const int N) {
    for (int i = 0; i < N; ++i) {
        C[i] = A[i] + B[i];
    }
}

void test_empty_vectors() {
    const int N = 0;
    std::vector<float> A(N, 1.0f);
    std::vector<float> B(N, 2.0f);
    std::vector<float> C(N, 0.0f);

    iKernel(A.data(), B.data(), C.data(), N);

    assert(C.size() == 0);
    std::cout << "test_empty_vectors passed." << std::endl;
}

void test_single_element_vectors() {
    const int N = 1;
    std::vector<float> A(N, 1.0f);
    std::vector<float> B(N, 2.0f);
    std::vector<float> C(N, 0.0f);

    iKernel(A.data(), B.data(), C.data(), N);

    assert(C[0] == 3.0f);
    std::cout << "test_single_element_vectors passed." << std::endl;
}

void test_large_vectors() {
    const int N = 1024 * 1024;
    std::vector<float> A(N, 1.0f);
    std::vector<float> B(N, 2.0f);
    std::vector<float> C(N, 0.0f);

    iKernel(A.data(), B.data(), C.data(), N);

    for (int i = 0; i < N; ++i) {
        assert(C[i] == 3.0f);
    }
    std::cout << "test_large_vectors passed." << std::endl;
}

void test_negative_values() {
    const int N = 10;
    std::vector<float> A(N, -1.0f);
    std::vector<float> B(N, -2.0f);
    std::vector<float> C(N, 0.0f);

    iKernel(A.data(), B.data(), C.data(), N);

    for (int i = 0; i < N; ++i) {
        assert(C[i] == -3.0f);
    }
    std::cout << "test_negative_values passed." << std::endl;
}

void test_mixed_values() {
    const int N = 5;
    std::vector<float> A = {1.0f, -1.0f, 0.0f, 2.5f, -3.5f};
    std::vector<float> B = {2.0f, 3.0f, -1.0f, -2.5f, 4.0f};
    std::vector<float> C(N, 0.0f);

    iKernel(A.data(), B.data(), C.data(), N);

    assert(C[0] == 3.0f);
    assert(C[1] == 2.0f);
    assert(C[2] == -1.0f);
    assert(C[3] == 0.0f);
    assert(C[4] == 0.5f);
    std::cout << "test_mixed_values passed." << std::endl;
}

int main() {
    test_empty_vectors();
    test_single_element_vectors();
    test_large_vectors();
    test_negative_values();
    test_mixed_values();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}