// Optimized code(id = 58): 

void pathPlan(int* devSpeed, int* devSteer, int size) {
    for (int tid = 0; tid < size; ++tid) {
        devSpeed[tid] += 1;
        devSteer[tid] += 1;
    }
}