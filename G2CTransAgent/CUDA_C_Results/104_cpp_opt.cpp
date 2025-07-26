// Optimized code(id = 104): 

#include <iostream>

void allAddInplace(double* arr, double alpha, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] += alpha;
    }
}

// Example usage:
// int main() {
//     const int n = 100;
//     double arr[n];
//     for (int i = 0; i < n; ++i) {
//         arr[i] = i;
//     }
//     double alpha = 5.0;
//     allAddInplace(arr, alpha, n);
//     for (int i = 0; i < n; ++i) {
//         std::cout << arr[i] << " ";
//     }
//     return 0;
// }