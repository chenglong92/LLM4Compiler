// Optimized code(id = 156): 

void allLog2Kernel(const double* arr, double* buf, int n) {
    for (int i = 0; i < n; ++i) {
        buf[i] = arr[i] / 2;
    }
}