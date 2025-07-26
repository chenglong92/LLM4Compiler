// Optimized code(id = 117): 

void add_vec_scalaire_cpu(int* vec, int* res, int a, long N) {
    for (long i = 0; i < N; ++i) {
        res[i] = vec[i] + a;
    }
}