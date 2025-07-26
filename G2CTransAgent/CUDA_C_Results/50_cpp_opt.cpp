// Optimized code(id = 50): 

void cuda_set_sg(int* sxz, int sxbeg, int szbeg, int jsx, int jsz, int ns, int npml, int nnz) {
    for (int id = 0; id < ns; ++id) {
        sxz[id] = nnz * (sxbeg + id * jsx + npml) + (szbeg + id * jsz + npml);
    }
}