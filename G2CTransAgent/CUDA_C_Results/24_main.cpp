// original code(id = 24): 
 /*
__global__ void get_boxes_for_nms ( const float * boxes_before_nms , const float * offset , float * boxes_for_nms , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( boxes_before_nms [ tid * 4 + 0 ] == ( -1 ) && boxes_before_nms [ tid * 4 + 1 ] == ( -1 ) && boxes_before_nms [ tid * 4 + 2 ] == ( -1 ) && boxes_before_nms [ tid * 4 + 3 ] == ( -1 ) ) { boxes_for_nms [ tid * 4 + 0 ] = ( -1 ) ; boxes_for_nms [ tid * 4 + 1 ] = ( -1 ) ; boxes_for_nms [ tid * 4 + 2 ] = ( -1 ) ; boxes_for_nms [ tid * 4 + 3 ] = ( -1 ) ; } else { boxes_for_nms [ tid * 4 + 0 ] = boxes_before_nms [ tid * 4 + 0 ] + offset [ tid ] ; boxes_for_nms [ tid * 4 + 1 ] = boxes_before_nms [ tid * 4 + 1 ] + offset [ tid ] ; boxes_for_nms [ tid * 4 + 2 ] = boxes_before_nms [ tid * 4 + 2 ] + offset [ tid ] ; boxes_for_nms [ tid * 4 + 3 ] = boxes_before_nms [ tid * 4 + 3 ] + offset [ tid ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void get_boxes_for_nms(const float* boxes_before_nms, const float* offset, float* boxes_for_nms, int dims);

        int main() {
            // Test case 1: All boxes are (-1, -1, -1, -1)
            {
                const int dims = 3;
                float boxes_before_nms[dims * 4] = {
                    -1, -1, -1, -1,
                    -1, -1, -1, -1,
                    -1, -1, -1, -1
                };
                float offset[dims] = {1.0f, 2.0f, 3.0f};
                float boxes_for_nms[dims * 4];
                
                get_boxes_for_nms(boxes_before_nms, offset, boxes_for_nms, dims);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(boxes_for_nms[i] == -1.0f);
                }
            }
            
            // Test case 2: No boxes are (-1, -1, -1, -1)
            {
                const int dims = 3;
                float boxes_before_nms[dims * 4] = {
                    1.0f, 2.0f, 3.0f, 4.0f,
                    5.0f, 6.0f, 7.0f, 8.0f,
                    9.0f, 10.0f, 11.0f, 12.0f
                };
                float offset[dims] = {1.0f, 2.0f, 3.0f};
                float boxes_for_nms[dims * 4];
                float expected[dims * 4] = {
                    2.0f, 3.0f, 4.0f, 5.0f,
                    7.0f, 8.0f, 9.0f, 10.0f,
                    12.0f, 13.0f, 14.0f, 15.0f
                };
                
                get_boxes_for_nms(boxes_before_nms, offset, boxes_for_nms, dims);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(boxes_for_nms[i] == expected[i]);
                }
            }
            
            // Test case 3: Mixed boxes (some (-1, -1, -1, -1), some not)
            {
                const int dims = 4;
                float boxes_before_nms[dims * 4] = {
                    -1, -1, -1, -1,
                    1.0f, 2.0f, 3.0f, 4.0f,
                    -1, -1, -1, -1,
                    5.0f, 6.0f, 7.0f, 8.0f
                };
                float offset[dims] = {1.0f, 2.0f, 3.0f, 4.0f};
                float boxes_for_nms[dims * 4];
                float expected[dims * 4] = {
                    -1, -1, -1, -1,
                    3.0f, 4.0f, 5.0f, 6.0f,
                    -1, -1, -1, -1,
                    9.0f, 10.0f, 11.0f, 12.0f
                };
                
                get_boxes_for_nms(boxes_before_nms, offset, boxes_for_nms, dims);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(boxes_for_nms[i] == expected[i]);
                }
            }
            
            // Test case 4: Single box (not (-1, -1, -1, -1))
            {
                const int dims = 1;
                float boxes_before_nms[dims * 4] = {1.0f, 2.0f, 3.0f, 4.0f};
                float offset[dims] = {5.0f};
                float boxes_for_nms[dims * 4];
                float expected[dims * 4] = {6.0f, 7.0f, 8.0f, 9.0f};
                
                get_boxes_for_nms(boxes_before_nms, offset, boxes_for_nms, dims);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(boxes_for_nms[i] == expected[i]);
                }
            }
            
            // Test case 5: Single box (-1, -1, -1, -1)
            {
                const int dims = 1;
                float boxes_before_nms[dims * 4] = {-1, -1, -1, -1};
                float offset[dims] = {5.0f};
                float boxes_for_nms[dims * 4];
                float expected[dims * 4] = {-1, -1, -1, -1};
                
                get_boxes_for_nms(boxes_before_nms, offset, boxes_for_nms, dims);
                
                for (int i = 0; i < dims * 4; ++i) {
                    assert(boxes_for_nms[i] == expected[i]);
                }
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }