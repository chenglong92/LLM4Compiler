// Optimized code(id = 161): 

#include <iostream>

void dadd_matrix(double* a, double* b, double* c, int N) {
    for (int idx = 0; idx < N; ++idx) {
        c[idx] = a[idx] + b[idx];
    }
}

// Example usage:
// int main() {
//     const int N = 100;
//     double a[N], b[N], c[N];
//     // Initialize a and b arrays
//     dadd_matrix(a, b, c, N);
//     // Use the results in c
//     return 0;
// }