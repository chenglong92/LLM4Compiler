// Optimized code(id = 57): 

void cpu_cross_correlate(float* Isg, float* Iss, float* sp, float* gp, int npml, int nnz, int nnx) {
            for (int i2 = npml; i2 < nnx - npml; ++i2) {
                for (int i1 = npml; i1 < nnz - npml; ++i1) {
                    int id = i1 + i2 * nnz;
                    float ps = sp[id];
                    float pg = gp[id];
                    Isg[id] += ps * pg;
                    Iss[id] += ps * ps;
                }
            }
        }