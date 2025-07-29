// original code(id = 5): 
 /*
__global__ void delay_kernel ( int * N_mobil , int * Tau , int dia ) { int N = N_mobil [ 0 ] ; int id = blockIdx . x * blockDim . x + threadIdx . x ; if ( id < N ) { if ( Tau [ id ] > 0 ) Tau [ id ] = Tau [ id ] - 1 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void delay_kernel(int* N_mobil, int* Tau, int dia);

        int main() {
            // Test case 1: All positive Tau values
            {
                int N = 3;
                int N_mobil[1] = {N};
                int Tau[3] = {5, 3, 1};
                delay_kernel(N_mobil, Tau, 0);
                assert(Tau[0] == 4);
                assert(Tau[1] == 2);
                assert(Tau[2] == 0);
            }

            // Test case 2: Mixed positive and non-positive Tau values
            {
                int N = 4;
                int N_mobil[1] = {N};
                int Tau[4] = {2, 0, -1, 3};
                delay_kernel(N_mobil, Tau, 0);
                assert(Tau[0] == 1);
                assert(Tau[1] == 0);
                assert(Tau[2] == -1);
                assert(Tau[3] == 2);
            }

            // Test case 3: Empty array (N=0)
            {
                int N = 0;
                int N_mobil[1] = {N};
                int Tau[1] = {5};  // Content shouldn't matter
                delay_kernel(N_mobil, Tau, 0);
                assert(Tau[0] == 5);  // Should remain unchanged
            }

            // Test case 4: All non-positive Tau values
            {
                int N = 3;
                int N_mobil[1] = {N};
                int Tau[3] = {0, -2, -5};
                delay_kernel(N_mobil, Tau, 0);
                assert(Tau[0] == 0);
                assert(Tau[1] == -2);
                assert(Tau[2] == -5);
            }

            // Test case 5: Single element array
            {
                int N = 1;
                int N_mobil[1] = {N};
                int Tau[1] = {10};
                delay_kernel(N_mobil, Tau, 0);
                assert(Tau[0] == 9);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void delay_kernel(int* N_mobil, int* Tau, int dia) {
            int N = N_mobil[0];
            for (int id = 0; id < N; ++id) {
                if (Tau[id] > 0) {
                    Tau[id] = Tau[id] - 1;
                }
            }
        }