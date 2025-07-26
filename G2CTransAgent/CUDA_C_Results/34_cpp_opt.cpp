// Optimized code(id = 34): 

void operacionCPU(float* u, float* lu, float u_m, float u_d, int n) {
    for (int idx = 0; idx < n; ++idx) {
        lu[idx] = (u[idx] - u_m) / u_d;
    }
}