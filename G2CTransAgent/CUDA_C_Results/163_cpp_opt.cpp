// Optimized code(id = 163): 

#include <iostream>

void cpu_add(float* c, float* a, float* b, int n) {
    for (int k = 0; k < n; ++k) {
        c[k] = a[k] + b[k];
    }
}

// Example usage:
// int main() {
//     const int n = 100;
//     float a[n], b[n], c[n];
//     // Initialize a and b arrays
//     for (int i = 0; i < n; ++i) {
//         a[i] = i;
//         b[i] = 2*i;
//     }
//     
//     cpu_add(c, a, b, n);
//     
//     // Print results
//     for (int i = 0; i < n; ++i) {
//         std::cout << c[i] << " ";
//     }
//     return 0;
// }