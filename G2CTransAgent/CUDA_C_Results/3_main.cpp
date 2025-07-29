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

        void test_set_valid_mask() {
            // Test case 1: All scores above threshold
            {
                const float scores[] = {0.8f, 0.9f, 1.0f, 1.1f};
                const float threshold = 0.7f;
                int mask[4];
                set_valid_mask(scores, threshold, mask, 4);
                assert(mask[0] == 1 && mask[1] == 1 && mask[2] == 1 && mask[3] == 1);
            }

            // Test case 2: All scores below threshold
            {
                const float scores[] = {0.4f, 0.5f, 0.6f, 0.3f};
                const float threshold = 0.7f;
                int mask[4];
                set_valid_mask(scores, threshold, mask, 4);
                assert(mask[0] == 0 && mask[1] == 0 && mask[2] == 0 && mask[3] == 0);
            }

            // Test case 3: Mixed scores
            {
                const float scores[] = {0.8f, 0.5f, 1.0f, 0.3f};
                const float threshold = 0.7f;
                int mask[4];
                set_valid_mask(scores, threshold, mask, 4);
                assert(mask[0] == 1 && mask[1] == 0 && mask[2] == 1 && mask[3] == 0);
            }

            // Test case 4: Empty array
            {
                const float scores[] = {};
                const float threshold = 0.7f;
                int mask[0];
                set_valid_mask(scores, threshold, mask, 0);
                // No assertion needed as it should just not crash
            }

            // Test case 5: Single element above threshold
            {
                const float scores[] = {0.8f};
                const float threshold = 0.7f;
                int mask[1];
                set_valid_mask(scores, threshold, mask, 1);
                assert(mask[0] == 1);
            }

            // Test case 6: Single element below threshold
            {
                const float scores[] = {0.6f};
                const float threshold = 0.7f;
                int mask[1];
                set_valid_mask(scores, threshold, mask, 1);
                assert(mask[0] == 0);
            }

            // Test case 7: Scores exactly at threshold (should be considered invalid)
            {
                const float scores[] = {0.7f, 0.7f, 0.7f};
                const float threshold = 0.7f;
                int mask[3];
                set_valid_mask(scores, threshold, mask, 3);
                assert(mask[0] == 0 && mask[1] == 0 && mask[2] == 0);
            }

            // Test case 8: Large array
            {
                const int size = 1000;
                float scores[size];
                int mask[size];
                for (int i = 0; i < size; ++i) {
                    scores[i] = (i % 2 == 0) ? 0.8f : 0.6f;
                }
                const float threshold = 0.7f;
                set_valid_mask(scores, threshold, mask, size);
                for (int i = 0; i < size; ++i) {
                    assert(mask[i] == (i % 2 == 0 ? 1 : 0));
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_set_valid_mask();
            return 0;
        }