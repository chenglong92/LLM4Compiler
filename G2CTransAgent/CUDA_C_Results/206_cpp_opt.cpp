// Optimized code(id = 206): 

void transferMBR3(double* xy_copy, long long* a_copy, int tasks) {
    for (int i = 0; i < tasks; ++i) {
        a_copy[i] = xy_copy[i] * 10000000;
    }
}