// Optimized code(id = 4): 

void delay_kernel(int* N_mobil, int* Tau, int dia) {
    int N = N_mobil[0];
    for (int id = 0; id < N; ++id) {
        if (Tau[id] > 0) {
            Tau[id] = Tau[id] - 1;
        }
    }
}