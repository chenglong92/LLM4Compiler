// Optimized code(id = 24): 

void get_boxes_for_nms(const float* boxes_before_nms, const float* offset, float* boxes_for_nms, int dims) {
    for (int tid = 0; tid < dims; ++tid) {
        if (boxes_before_nms[tid * 4 + 0] == (-1) && 
            boxes_before_nms[tid * 4 + 1] == (-1) && 
            boxes_before_nms[tid * 4 + 2] == (-1) && 
            boxes_before_nms[tid * 4 + 3] == (-1)) {
            boxes_for_nms[tid * 4 + 0] = (-1);
            boxes_for_nms[tid * 4 + 1] = (-1);
            boxes_for_nms[tid * 4 + 2] = (-1);
            boxes_for_nms[tid * 4 + 3] = (-1);
        } else {
            boxes_for_nms[tid * 4 + 0] = boxes_before_nms[tid * 4 + 0] + offset[tid];
            boxes_for_nms[tid * 4 + 1] = boxes_before_nms[tid * 4 + 1] + offset[tid];
            boxes_for_nms[tid * 4 + 2] = boxes_before_nms[tid * 4 + 2] + offset[tid];
            boxes_for_nms[tid * 4 + 3] = boxes_before_nms[tid * 4 + 3] + offset[tid];
        }
    }
}