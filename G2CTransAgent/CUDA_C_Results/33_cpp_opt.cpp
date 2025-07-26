// Optimized code(id = 33): 

void colLog2SumExp2(const double* mat, double* buf, int m, int n) {
    for (int j = 0; j < n; ++j) {
        double maximum = mat[j];
        for (int i = 1; i < m; ++i) {
            if (mat[i * n + j] > maximum) {
                maximum = mat[i * n + j];
            }
        }
        
        double res = 0.0;
        for (int i = 0; i < m; ++i) {
            res += exp(mat[i * n + j] - maximum);
        }
        
        buf[j] = log(res) + maximum;
    }
}