// Optimized code(id = 71): 

#include <cmath>

void kComputeActs(const float* d_nets, float* d_acts, int size) {
    for (int un_idx = 0; un_idx < size; ++un_idx) {
        float tact = 1.0f / (1.0f + expf(-d_acts[un_idx]));
        d_acts[un_idx] = tact;
    }
}