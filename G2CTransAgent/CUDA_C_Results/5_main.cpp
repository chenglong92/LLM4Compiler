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
                int N = 5;
                int N_mobil[1] = {N};
                int Tau[] = {3, 5, 2, 1, 4};
                int expected[] = {2, 4, 1, 0, 3};
                
                delay_kernel(N_mobil, Tau, 0);
                
                for (int i = 0; i < N; ++i) {
                    assert(Tau[i] == expected[i]);
                }
            }

            // Test case 2: Mixed positive, zero and negative Tau values
            {
                int N = 6;
                int N_mobil[1] = {N};
                int Tau[] = {0, -1, 3, -2, 1, 0};
                int expected[] = {0, -1, 2, -2, 0, 0};
                
                delay_kernel(N_mobil, Tau, 0);
                
                for (int i = 0; i < N; ++i) {
                    assert(Tau[i] == expected[i]);
                }
            }

            // Test case 3: Empty array (N = 0)
            {
                int N = 0;
                int N_mobil[1] = {N};
                int Tau[] = {1, 2, 3};  // Shouldn't be accessed
                
                delay_kernel(N_mobil, Tau, 0);
                
                // No assertions needed as function shouldn't modify anything
            }

            // Test case 4: All zero Tau values
            {
                int N = 4;
                int N_mobil[1] = {N};
                int Tau[] = {0, 0, 0, 0};
                int expected[] = {0, 0, 0, 0};
                
                delay_kernel(N_mobil, Tau, 0);
                
                for (int i = 0; i < N; ++i) {
                    assert(Tau[i] == expected[i]);
                }
            }

            // Test case 5: All negative Tau values
            {
                int N = 3;
                int N_mobil[1] = {N};
                int Tau[] = {-1, -5, -3};
                int expected[] = {-1, -5, -3};
                
                delay_kernel(N_mobil, Tau, 0);
                
                for (int i = 0; i < N; ++i) {
                    assert(Tau[i] == expected[i]);
                }
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