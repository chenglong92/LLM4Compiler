// original code(id = 188): 
 /*
__global__ void returnResult ( const float * box , const float * score , const int * label , float * box_out , float * score_out , int * label_out , float score_thr , const int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( score [ tid ] < score_thr ) { score_out [ tid ] = 0 ; box_out [ tid * 4 + 0 ] = -1 ; box_out [ tid * 4 + 1 ] = -1 ; box_out [ tid * 4 + 2 ] = -1 ; box_out [ tid * 4 + 3 ] = -1 ; label_out [ tid ] = -1 ; } else { score_out [ tid ] = score [ tid ] ; box_out [ tid * 4 + 0 ] = box [ tid * 4 + 0 ] ; box_out [ tid * 4 + 1 ] = box [ tid * 4 + 1 ] ; box_out [ tid * 4 + 2 ] = box [ tid * 4 + 2 ] ; box_out [ tid * 4 + 3 ] = box [ tid * 4 + 3 ] ; label_out [ tid ] = label [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void returnResult(const float* box, const float* score, const int* label, float* box_out, float* score_out, int* label_out, float score_thr, const int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (score[tid] < score_thr) {
                    score_out[tid] = 0;
                    box_out[tid * 4 + 0] = -1;
                    box_out[tid * 4 + 1] = -1;
                    box_out[tid * 4 + 2] = -1;
                    box_out[tid * 4 + 3] = -1;
                    label_out[tid] = -1;
                } else {
                    score_out[tid] = score[tid];
                    box_out[tid * 4 + 0] = box[tid * 4 + 0];
                    box_out[tid * 4 + 1] = box[tid * 4 + 1];
                    box_out[tid * 4 + 2] = box[tid * 4 + 2];
                    box_out[tid * 4 + 3] = box[tid * 4 + 3];
                    label_out[tid] = label[tid];
                }
            }
        }

        int main() {
            // Test case 1: All scores below threshold
            {
                const int dims = 3;
                float box[dims * 4] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f};
                float score[dims] = {0.1f, 0.2f, 0.3f};
                int label[dims] = {1, 2, 3};
                float box_out[dims * 4];
                float score_out[dims];
                int label_out[dims];
                float score_thr = 0.5f;

                returnResult(box, score, label, box_out, score_out, label_out, score_thr, dims);

                for (int i = 0; i < dims; ++i) {
                    assert(score_out[i] == 0.0f);
                    assert(label_out[i] == -1);
                }
                for (int i = 0; i < dims * 4; ++i) {
                    assert(box_out[i] == -1.0f);
                }
            }

            // Test case 2: All scores above threshold
            {
                const int dims = 2;
                float box[dims * 4] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f};
                float score[dims] = {0.9f, 0.8f};
                int label[dims] = {10, 20};
                float box_out[dims * 4];
                float score_out[dims];
                int label_out[dims];
                float score_thr = 0.5f;

                returnResult(box, score, label, box_out, score_out, label_out, score_thr, dims);

                for (int i = 0; i < dims; ++i) {
                    assert(score_out[i] == score[i]);
                    assert(label_out[i] == label[i]);
                }
                for (int i = 0; i < dims * 4; ++i) {
                    assert(box_out[i] == box[i]);
                }
            }

            // Test case 3: Mixed scores (some above, some below threshold)
            {
                const int dims = 4;
                float box[dims * 4] = {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 
                                      3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f};
                float score[dims] = {0.6f, 0.4f, 0.7f, 0.3f};
                int label[dims] = {1, 2, 3, 4};
                float box_out[dims * 4];
                float score_out[dims];
                int label_out[dims];
                float score_thr = 0.5f;

                returnResult(box, score, label, box_out, score_out, label_out, score_thr, dims);

                assert(score_out[0] == 0.6f);
                assert(score_out[1] == 0.0f);
                assert(score_out[2] == 0.7f);
                assert(score_out[3] == 0.0f);

                assert(label_out[0] == 1);
                assert(label_out[1] == -1);
                assert(label_out[2] == 3);
                assert(label_out[3] == -1);

                for (int i = 0; i < 4; ++i) {
                    assert(box_out[i] == box[i]); // First box (above threshold)
                }
                for (int i = 4; i < 8; ++i) {
                    assert(box_out[i] == -1.0f); // Second box (below threshold)
                }
                for (int i = 8; i < 12; ++i) {
                    assert(box_out[i] == box[i]); // Third box (above threshold)
                }
                for (int i = 12; i < 16; ++i) {
                    assert(box_out[i] == -1.0f); // Fourth box (below threshold)
                }
            }

            // Test case 4: Empty input (dims = 0)
            {
                const int dims = 0;
                float box[1] = {0.0f}; // Dummy
                float score[1] = {0.0f};
                int label[1] = {0};
                float box_out[1];
                float score_out[1];
                int label_out[1];
                float score_thr = 0.5f;

                returnResult(box, score, label, box_out, score_out, label_out, score_thr, dims);
                // No assertions needed as function shouldn't process anything
            }

            // Test case 5: Edge case - score exactly at threshold
            {
                const int dims = 2;
                float box[dims * 4] = {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f};
                float score[dims] = {0.5f, 0.5f};
                int label[dims] = {1, 2};
                float box_out[dims * 4];
                float score_out[dims];
                int label_out[dims];
                float score_thr = 0.5f;

                returnResult(box, score, label, box_out, score_out, label_out, score_thr, dims);

                assert(score_out[0] == 0.5f);
                assert(score_out[1] == 0.5f);
                assert(label_out[0] == 1);
                assert(label_out[1] == 2);
                for (int i = 0; i < dims * 4; ++i) {
                    assert(box_out[i] == box[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }