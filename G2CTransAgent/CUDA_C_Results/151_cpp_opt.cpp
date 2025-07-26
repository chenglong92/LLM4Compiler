// Optimized code(id = 151): 

#include <cstdio>
        #include <cstdint>

        void check_results(uint* g_results0, uint* g_results1, int n) {
            for (int gidx = 0; gidx < n; ++gidx) {
                uint result0 = g_results0[gidx];
                uint result1 = g_results1[gidx];
                if (result0 != result1) {
                    printf("%i != %i for thread %i\n", result0, result1, gidx);
                }
            }
        }