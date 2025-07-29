// original code(id = 0): 
 /*
__global__ void add_sources_d ( const float * const model , float * wfp , const float * const source_amplitude , const int * const sources_z , const int * const sources_x , const int nz , const int nx , const int nt , const int ns , const int it ) { int x = threadIdx . x ; int b = blockIdx . x ; int i = sources_z [ b * ns + x ] * nx + sources_x [ b * ns + x ] ; int ib = b * nz * nx + i ; wfp [ ib ] += source_amplitude [ b * ns * nt + x * nt + it ] * model [ i ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void add_sources_d(const float* const model, float* wfp, const float* const source_amplitude, const int* const sources_z, const int* const sources_x, const int nz, const int nx, const int nt, const int ns, const int it);

        int main() {
            // Test case 1: Single source, single time step
            {
                const int nz = 5, nx = 5, nt = 10, ns = 1, it = 0;
                float model[nz * nx] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                                        1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
                float wfp[ns * nz * nx] = {0};
                float source_amplitude[ns * ns * nt] = {2.0f};
                int sources_z[ns * ns] = {2};
                int sources_x[ns * ns] = {2};

                add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

                // Only the source position should be updated
                for (int i = 0; i < ns * nz * nx; ++i) {
                    if (i == 2 * nx + 2) {
                        assert(wfp[i] == 2.0f);
                    } else {
                        assert(wfp[i] == 0.0f);
                    }
                }
            }

            // Test case 2: Multiple sources, single time step
            {
                const int nz = 3, nx = 3, nt = 5, ns = 2, it = 0;
                float model[nz * nx] = {1.0f, 2.0f, 3.0f,
                                        4.0f, 5.0f, 6.0f,
                                        7.0f, 8.0f, 9.0f};
                float wfp[ns * nz * nx] = {0};
                float source_amplitude[ns * ns * nt] = {1.0f, 2.0f, 3.0f, 4.0f};
                int sources_z[ns * ns] = {0, 1, 1, 2};
                int sources_x[ns * ns] = {0, 1, 2, 0};

                add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

                // Check first source batch
                assert(wfp[0 * nz * nx + 0 * nx + 0] == 1.0f * model[0 * nx + 0]);  // source 0,0
                assert(wfp[0 * nz * nx + 1 * nx + 1] == 2.0f * model[1 * nx + 1]);  // source 0,1

                // Check second source batch
                assert(wfp[1 * nz * nx + 1 * nx + 2] == 3.0f * model[1 * nx + 2]);  // source 1,2
                assert(wfp[1 * nz * nx + 2 * nx + 0] == 4.0f * model[2 * nx + 0]);  // source 1,0
            }

            // Test case 3: Edge cases - sources at boundaries
            {
                const int nz = 2, nx = 2, nt = 3, ns = 1, it = 1;
                float model[nz * nx] = {0.5f, 1.5f, 2.5f, 3.5f};
                float wfp[ns * nz * nx] = {0};
                float source_amplitude[ns * ns * nt] = {1.0f, 2.0f, 3.0f};
                int sources_z[ns * ns] = {0};
                int sources_x[ns * ns] = {1};

                add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

                assert(wfp[0 * nz * nx + 0 * nx + 1] == 2.0f * model[0 * nx + 1]);
            }

            // Test case 4: Multiple time steps
            {
                const int nz = 2, nx = 2, nt = 2, ns = 1, it = 1;
                float model[nz * nx] = {1.0f, 1.0f, 1.0f, 1.0f};
                float wfp[ns * nz * nx] = {0};
                float source_amplitude[ns * ns * nt] = {1.0f, 2.0f};
                int sources_z[ns * ns] = {0};
                int sources_x[ns * ns] = {0};

                add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

                assert(wfp[0 * nz * nx + 0 * nx + 0] == 2.0f * model[0 * nx + 0]);
            }

            // Test case 5: Zero sources
            {
                const int nz = 2, nx = 2, nt = 1, ns = 0, it = 0;
                float model[nz * nx] = {1.0f, 1.0f, 1.0f, 1.0f};
                float wfp[1] = {0};  // dummy, won't be accessed
                float source_amplitude[1] = {0};  // dummy
                int sources_z[1] = {0};  // dummy
                int sources_x[1] = {0};  // dummy

                add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);
                // Should not crash or produce errors
            }

            std::cout << "All tests passed!" << std::endl;
            return 0;
        }

        void add_sources_d(const float* const model, float* wfp, const float* const source_amplitude, const int* const sources_z, const int* const sources_x, const int nz, const int nx, const int nt, const int ns, const int it) {
            for (int b = 0; b < ns; ++b) {
                for (int x = 0; x < ns; ++x) {
                    int i = sources_z[b * ns + x] * nx + sources_x[b * ns + x];
                    int ib = b * nz * nx + i;
                    wfp[ib] += source_amplitude[b * ns * nt + x * nt + it] * model[i];
                }
            }
        }