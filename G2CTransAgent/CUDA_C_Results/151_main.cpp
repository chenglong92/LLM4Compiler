// original code(id = 151): 
 /*
__global__ void check_results_kernel ( uint * g_results0 , uint * g_results1 , int n ) { uint idx = threadIdx . x ; uint gidx = blockDim . x * blockIdx . x + idx ; uint result0 ; uint result1 ; if ( gidx < n ) { result0 = g_results0 [ gidx ] ; result1 = g_results1 [ gidx ] ; if ( result0 != result1 ) { printf ( " % i ▁ ! = ▁ % i ▁ for ▁ thread ▁ % i ▁ \n " , result0 , result1 , gidx ) ; } } }
*/
// optimized code: 

#include <cstdio>
        #include <cstdint>
        #include <cstdlib>
        #include <ctime>

        void check_results(uint* g_results0, uint* g_results1, int n) {
            for (int gidx = 0; gidx < n; ++gidx) {
                uint result0 = g_results0[gidx];
                uint result1 = g_results1[gidx];
                if (result0 != result1) {
                    printf("%i != %i for thread %i\n", result0, result1, gidx);
                }
            }
        }

        int main() {
            // Test case 1: All elements are equal
            {
                const int n = 5;
                uint results0[n] = {1, 2, 3, 4, 5};
                uint results1[n] = {1, 2, 3, 4, 5};
                printf("Test case 1: All elements equal - should produce no output\n");
                check_results(results0, results1, n);
            }

            // Test case 2: Some elements differ
            {
                const int n = 5;
                uint results0[n] = {1, 2, 3, 4, 5};
                uint results1[n] = {1, 0, 3, 0, 5};
                printf("\nTest case 2: Some elements differ - should show mismatches for indices 1 and 3\n");
                check_results(results0, results1, n);
            }

            // Test case 3: All elements differ
            {
                const int n = 3;
                uint results0[n] = {10, 20, 30};
                uint results1[n] = {11, 22, 33};
                printf("\nTest case 3: All elements differ - should show mismatches for all indices\n");
                check_results(results0, results1, n);
            }

            // Test case 4: Empty arrays
            {
                const int n = 0;
                uint* results0 = nullptr;
                uint* results1 = nullptr;
                printf("\nTest case 4: Empty arrays - should produce no output\n");
                check_results(results0, results1, n);
            }

            // Test case 5: Random test
            {
                srand(time(nullptr));
                const int n = 10;
                uint results0[n];
                uint results1[n];
                for (int i = 0; i < n; ++i) {
                    results0[i] = rand() % 100;
                    results1[i] = (rand() % 2) ? results0[i] : (rand() % 100);
                }
                printf("\nTest case 5: Random test - may show mismatches\n");
                check_results(results0, results1, n);
            }

            return 0;
        }