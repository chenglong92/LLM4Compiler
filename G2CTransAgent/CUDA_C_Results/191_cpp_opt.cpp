// Optimized code(id = 191): 

void cuda_record(float* p, float* seis_kt, int* Gxz, int ng) {
            for (int id = 0; id < ng; ++id) {
                seis_kt[id] = p[Gxz[id]];
            }
        }