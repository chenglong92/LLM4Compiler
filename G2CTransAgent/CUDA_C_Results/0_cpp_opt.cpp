// Optimized code(id = 0): 

void add_sources_d(const float* const model, float* wfp, const float* const source_amplitude, const int* const sources_z, const int* const sources_x, const int nz, const int nx, const int nt, const int ns, const int it) {
            for (int b = 0; b < ns; ++b) {
                for (int x = 0; x < ns; ++x) {
                    int i = sources_z[b * ns + x] * nx + sources_x[b * ns + x];
                    int ib = b * nz * nx + i;
                    wfp[ib] += source_amplitude[b * ns * nt + x * nt + it] * model[i];
                }
            }
        }