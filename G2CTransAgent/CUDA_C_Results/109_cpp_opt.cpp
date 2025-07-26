// Optimized code(id = 109): 

#include <iostream>

void matrixMultiply(float* A, float* B, float* C, int numARows, int numAColumns, int numBRows, int numBColumns) {
    int numCRows = numARows;
    int numCColumns = numBColumns;

    for (int row = 0; row < numCRows; ++row) {
        for (int col = 0; col < numCColumns; ++col) {
            float sum = 0.0f;
            for (int k = 0; k < numBRows; ++k) {
                sum += A[row * numAColumns + k] * B[k * numBColumns + col];
            }
            C[row * numCColumns + col] = sum;
        }
    }
}

// Example usage:
// int main() {
//     const int numARows = 3, numAColumns = 2;
//     const int numBRows = 2, numBColumns = 4;
//     float A[numARows * numAColumns] = {1,2,3,4,5,6};
//     float B[numBRows * numBColumns] = {1,2,3,4,5,6,7,8};
//     float C[numARows * numBColumns] = {0};
//     
//     matrixMultiply(A, B, C, numARows, numAColumns, numBRows, numBColumns);
//     
//     for (int i = 0; i < numARows; ++i) {
//         for (int j = 0; j < numBColumns; ++j) {
//             std::cout << C[i * numBColumns + j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }