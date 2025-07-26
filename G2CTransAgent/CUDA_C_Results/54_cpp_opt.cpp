// Optimized code(id = 54): 

#include <iostream>

void cpu_matrix_mult(int* a, int* b, int* c, int m, int n, int k) {
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < k; ++col) {
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += a[row * n + i] * b[i * k + col];
            }
            c[row * k + col] = sum;
        }
    }
}

// Example usage:
// int main() {
//     const int m = 3, n = 2, k = 3;
//     int a[m*n] = {1,2,3,4,5,6};
//     int b[n*k] = {7,8,9,10,11,12};
//     int c[m*k] = {0};
//     
//     cpu_matrix_mult(a, b, c, m, n, k);
//     
//     for (int i = 0; i < m; ++i) {
//         for (int j = 0; j < k; ++j) {
//             std::cout << c[i*k + j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }