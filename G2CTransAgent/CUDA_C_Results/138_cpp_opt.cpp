// Optimized code(id = 138): 

void cuda_laplace_filter(float* Img, float* laplace, float _dz, float _dx, int npml, int nnz, int nnx) {
    for (int i2 = 0; i2 < nnx; ++i2) {
        for (int i1 = 0; i1 < nnz; ++i1) {
            int id = i1 + i2 * nnz;
            float diff1 = 0.0f;
            float diff2 = 0.0f;
            
            if (i1 >= npml && i1 < nnz - npml && i2 >= npml && i2 < nnx - npml) {
                diff1 = Img[id + 1] - 2.0f * Img[id] + Img[id - 1];
                diff2 = Img[id + nnz] - 2.0f * Img[id] + Img[id - nnz];
            }
            
            laplace[id] = _dz * _dz * diff1 + _dx * _dx * diff2;
        }
    }
}