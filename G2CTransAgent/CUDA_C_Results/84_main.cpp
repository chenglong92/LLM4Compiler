// original code(id = 84): 
 /*
__global__ void resizedClsScore ( const float * score , const float * score_factors , float * output , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( score [ tid ] == ( -1 ) ) { output [ tid ] = -1 ; } else { output [ tid ] = score [ tid ] * score_factors [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void resizedClsScore(const float* score, const float* score_factors, float* output, int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (score[tid] == (-1)) {
            output[tid] = -1;
        } else {
            output[tid] = score[tid] * score_factors[tid];
        }
    }
}

void test_case_1() {
    const int dims = 3;
    float score[dims] = {1.0f, -1.0f, 2.0f};
    float score_factors[dims] = {2.0f, 3.0f, 4.0f};
    float output[dims];
    
    resizedClsScore(score, score_factors, output, dims);
    
    assert(output[0] == 2.0f);
    assert(output[1] == -1.0f);
    assert(output[2] == 8.0f);
    std::cout << "Test Case 1 Passed" << std::endl;
}

void test_case_2() {
    const int dims = 5;
    float score[dims] = {0.5f, 1.5f, 2.5f, 3.5f, -1.0f};
    float score_factors[dims] = {2.0f, 2.0f, 2.0f, 2.0f, 5.0f};
    float output[dims];
    
    resizedClsScore(score, score_factors, output, dims);
    
    assert(output[0] == 1.0f);
    assert(output[1] == 3.0f);
    assert(output[2] == 5.0f);
    assert(output[3] == 7.0f);
    assert(output[4] == -1.0f);
    std::cout << "Test Case 2 Passed" << std::endl;
}

void test_case_3() {
    const int dims = 1;
    float score[dims] = {-1.0f};
    float score_factors[dims] = {10.0f};
    float output[dims];
    
    resizedClsScore(score, score_factors, output, dims);
    
    assert(output[0] == -1.0f);
    std::cout << "Test Case 3 Passed" << std::endl;
}

void test_case_4() {
    const int dims = 4;
    float score[dims] = {1.0f, 2.0f, 3.0f, 4.0f};
    float score_factors[dims] = {0.5f, 0.5f, 0.5f, 0.5f};
    float output[dims];
    
    resizedClsScore(score, score_factors, output, dims);
    
    assert(output[0] == 0.5f);
    assert(output[1] == 1.0f);
    assert(output[2] == 1.5f);
    assert(output[3] == 2.0f);
    std::cout << "Test Case 4 Passed" << std::endl;
}

void test_case_5() {
    const int dims = 2;
    float score[dims] = {0.0f, -1.0f};
    float score_factors[dims] = {1.0f, 1.0f};
    float output[dims];
    
    resizedClsScore(score, score_factors, output, dims);
    
    assert(output[0] == 0.0f);
    assert(output[1] == -1.0f);
    std::cout << "Test Case 5 Passed" << std::endl;
}

int main() {
    test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}