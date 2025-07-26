// Optimized code(id = 152): 

void get_conf_inds(const float* mlvl_conf, const float conf_thr, int* conf_inds, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (mlvl_conf[tid] >= conf_thr) {
                    conf_inds[tid] = 1;
                } else {
                    conf_inds[tid] = -1;
                }
            }
        }