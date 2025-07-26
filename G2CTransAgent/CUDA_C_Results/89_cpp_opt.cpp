// Optimized code(id = 89): 

void sum_array_1Dgrid_1Dblock(float* a, float* b, float* c, int nx) {
    for (int gid = 0; gid < nx; ++gid) {
        c[gid] = a[gid] + b[gid];
    }
}