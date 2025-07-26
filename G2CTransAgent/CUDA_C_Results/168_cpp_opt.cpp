// Optimized code(id = 168): 

void multMat(int n, int* arrForce_d, int* arrDistance_d, int* arrAnswer_d) {
    for (int i = 0; i < n; ++i) {
        arrAnswer_d[i] = arrForce_d[i] * arrDistance_d[i];
    }
}