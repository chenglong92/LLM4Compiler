// Optimized code(id = 31): 

void sum_arrays_cpu(int* a, int* b, int* c, int size) {
    for (int index = 0; index < size; ++index) {
        c[index] = a[index] + b[index];
    }
}