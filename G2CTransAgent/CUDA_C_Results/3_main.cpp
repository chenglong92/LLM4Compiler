// original code(id = 3): 
 /*
__global__ void set_valid_mask ( const float * score , float score_thr , int * valid_mask , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( score [ tid ] > score_thr ) { valid_mask [ tid ] = 1 ; } else { valid_mask [ tid ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void set_valid_mask(const float* score, float score_thr, int* valid_mask, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (score[tid] > score_thr) {
                    valid_mask[tid] = 1;
                } else {
                    valid_mask[tid] = 0;
                }
            }
        }

        void test_all_above_threshold() {
            const int dims = 5;
            float scores[dims] = {0.9f, 1.1f, 2.0f, 3.5f, 0.6f};
            float threshold = 0.5f;
            int valid_mask[dims] = {0};
            
            set_valid_mask(scores, threshold, valid_mask, dims);
            
            for (int i = 0; i < dims; ++i) {
                assert(valid_mask[i] == 1);
            }
            std::cout << "test_all_above_threshold passed" << std::endl;
        }

        void test_all_below_threshold() {
            const int dims = 4;
            float scores[dims] = {0.1f, 0.2f, 0.3f, 0.4f};
            float threshold = 0.5f;
            int valid_mask[dims] = {0};
            
            set_valid_mask(scores, threshold, valid_mask, dims);
            
            for (int i = 0; i < dims; ++i) {
                assert(valid_mask[i] == 0);
            }
            std::cout << "test_all_below_threshold passed" << std::endl;
        }

        void test_mixed_scores() {
            const int dims = 6;
            float scores[dims] = {0.1f, 0.6f, 0.4f, 0.7f, 0.3f, 0.9f};
            float threshold = 0.5f;
            int valid_mask[dims] = {0};
            int expected[dims] = {0, 1, 0, 1, 0, 1};
            
            set_valid_mask(scores, threshold, valid_mask, dims);
            
            for (int i = 0; i < dims; ++i) {
                assert(valid_mask[i] == expected[i]);
            }
            std::cout << "test_mixed_scores passed" << std::endl;
        }

        void test_empty_array() {
            const int dims = 0;
            float scores[1] = {0.0f};  // dummy
            float threshold = 0.5f;
            int valid_mask[1] = {0};   // dummy
            
            set_valid_mask(scores, threshold, valid_mask, dims);
            // Should not crash or produce any errors
            std::cout << "test_empty_array passed" << std::endl;
        }

        void test_equal_to_threshold() {
            const int dims = 3;
            float scores[dims] = {0.5f, 0.5f, 0.5f};
            float threshold = 0.5f;
            int valid_mask[dims] = {0};
            
            set_valid_mask(scores, threshold, valid_mask, dims);
            
            for (int i = 0; i < dims; ++i) {
                assert(valid_mask[i] == 0);
            }
            std::cout << "test_equal_to_threshold passed" << std::endl;
        }

        int main() {
            test_all_above_threshold();
            test_all_below_threshold();
            test_mixed_scores();
            test_empty_array();
            test_equal_to_threshold();
            
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }