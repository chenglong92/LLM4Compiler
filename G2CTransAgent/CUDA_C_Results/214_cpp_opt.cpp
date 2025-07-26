// Optimized code(id = 214): 

void setLabels(int* output, int dims, int clsNum) {
    for (int tid = 0; tid < dims; ++tid) {
        output[tid] = tid % clsNum;
    }
}