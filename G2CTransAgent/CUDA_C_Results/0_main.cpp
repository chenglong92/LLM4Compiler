// original code(id = 0): 
 /*
__global__ void add_sources_d ( const float * const model , float * wfp , const float * const source_amplitude , const int * const sources_z , const int * const sources_x , const int nz , const int nx , const int nt , const int ns , const int it ) { int x = threadIdx . x ; int b = blockIdx . x ; int i = sources_z [ b * ns + x ] * nx + sources_x [ b * ns + x ] ; int ib = b * nz * nx + i ; wfp [ ib ] += source_amplitude [ b * ns * nt + x * nt + it ] * model [ i ] ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

void add_sources_d(const float* const model, float* wfp, const float* const source_amplitude, 
                  const int* const sources_z, const int* const sources_x, 
                  const int nz, const int nx, const int nt, const int ns, const int it) {
    for (int b = 0; b < ns; ++b) {
        for (int x = 0; x < ns; ++x) {
            int i = sources_z[b * ns + x] * nx + sources_x[b * ns + x];
            int ib = b * nz * nx + i;
            wfp[ib] += source_amplitude[b * ns * nt + x * nt + it] * model[i];
        }
    }
}

void test_add_sources_d_basic() {
    const int nz = 3;
    const int nx = 3;
    const int nt = 2;
    const int ns = 2;
    const int it = 1;

    float model[nz * nx] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float wfp[ns * nz * nx] = {0};
    float source_amplitude[ns * ns * nt] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f};
    int sources_z[ns * ns] = {0, 1, 1, 2};
    int sources_x[ns * ns] = {0, 1, 2, 0};

    add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

    assert(wfp[0 * nz * nx + 0 * nx + 0] == 0.0f); // Not modified
    assert(wfp[0 * nz * nx + 1 * nx + 1] == 0.6f * 5.0f); // b=0, x=1
    assert(wfp[1 * nz * nx + 1 * nx + 2] == 0.8f * 7.0f); // b=1, x=1
}

void test_add_sources_d_edge_case_empty() {
    const int nz = 1;
    const int nx = 1;
    const int nt = 1;
    const int ns = 0;
    const int it = 0;

    float model[nz * nx] = {1.0f};
    float wfp[1] = {0}; // Dummy, won't be accessed
    float source_amplitude[1] = {0}; // Dummy
    int sources_z[1] = {0}; // Dummy
    int sources_x[1] = {0}; // Dummy

    add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);
    // No assertion, just checking it doesn't crash
}

void test_add_sources_d_single_source() {
    const int nz = 2;
    const int nx = 2;
    const int nt = 1;
    const int ns = 1;
    const int it = 0;

    float model[nz * nx] = {1.0f, 2.0f, 3.0f, 4.0f};
    float wfp[ns * nz * nx] = {0};
    float source_amplitude[ns * ns * nt] = {0.5f};
    int sources_z[ns * ns] = {1};
    int sources_x[ns * ns] = {1};

    add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

    assert(wfp[0 * nz * nx + 1 * nx + 1] == 0.5f * 4.0f);
}

void test_add_sources_d_random_values() {
    const int nz = 4;
    const int nx = 4;
    const int nt = 3;
    const int ns = 2;
    const int it = 2;

    float model[nz * nx];
    float wfp[ns * nz * nx] = {0};
    float source_amplitude[ns * ns * nt];
    int sources_z[ns * ns];
    int sources_x[ns * ns];

    // Initialize with random values
    srand(time(nullptr));
    for (int i = 0; i < nz * nx; ++i) model[i] = static_cast<float>(rand()) / RAND_MAX;
    for (int i = 0; i < ns * ns * nt; ++i) source_amplitude[i] = static_cast<float>(rand()) / RAND_MAX;
    for (int i = 0; i < ns * ns; ++i) {
        sources_z[i] = rand() % nz;
        sources_x[i] = rand() % nx;
    }

    add_sources_d(model, wfp, source_amplitude, sources_z, sources_x, nz, nx, nt, ns, it);

    // Verify calculations for random values
    for (int b = 0; b < ns; ++b) {
        for (int x = 0; x < ns; ++x) {
            int i = sources_z[b * ns + x] * nx + sources_x[b * ns + x];
            int ib = b * nz * nx + i;
            float expected = source_amplitude[b * ns * nt + x * nt + it] * model[i];
            assert(wfp[ib] == expected);
        }
    }
}

int main() {
    test_add_sources_d_basic();
    test_add_sources_d_edge_case_empty();
    test_add_sources_d_single_source();
    test_add_sources_d_random_values();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}