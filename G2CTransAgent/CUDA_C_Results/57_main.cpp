// original code(id = 57): 
 /*
__global__ void cuda_cross_correlate ( float * Isg , float * Iss , float * sp , float * gp , int npml , int nnz , int nnx ) { int i1 = threadIdx . x + blockDim . x * blockIdx . x ; int i2 = threadIdx . y + blockDim . y * blockIdx . y ; int id = i1 + i2 * nnz ; if ( i1 >= npml && i1 < nnz - npml && i2 >= npml && i2 < nnx - npml ) { float ps = sp [ id ] ; float pg = gp [ id ] ; Isg [ id ] += ps * pg ; Iss [ id ] += ps * ps ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void cpu_cross_correlate(float* Isg, float* Iss, float* sp, float* gp, int npml, int nnz, int nnx);

        int main() {
            // Test Case 1: Basic functionality with small arrays
            {
                const int npml = 1;
                const int nnz = 4;
                const int nnx = 4;
                float Isg[nnz * nnx] = {0};
                float Iss[nnz * nnx] = {0};
                float sp[nnz * nnx] = {1.0f, 2.0f, 3.0f, 4.0f,
                                       5.0f, 6.0f, 7.0f, 8.0f,
                                       9.0f, 10.0f, 11.0f, 12.0f,
                                       13.0f, 14.0f, 15.0f, 16.0f};
                float gp[nnz * nnx] = {0.5f, 1.5f, 2.5f, 3.5f,
                                       4.5f, 5.5f, 6.5f, 7.5f,
                                       8.5f, 9.5f, 10.5f, 11.5f,
                                       12.5f, 13.5f, 14.5f, 15.5f};

                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);

                // Check inner points (excluding PML)
                assert(fabs(Isg[5] - (6.0f * 5.5f)) < 1e-6f);
                assert(fabs(Isg[6] - (7.0f * 6.5f)) < 1e-6f);
                assert(fabs(Isg[9] - (10.0f * 9.5f)) < 1e-6f);
                assert(fabs(Isg[10] - (11.0f * 10.5f)) < 1e-6f);

                assert(fabs(Iss[5] - (6.0f * 6.0f)) < 1e-6f);
                assert(fabs(Iss[6] - (7.0f * 7.0f)) < 1e-6f);
                assert(fabs(Iss[9] - (10.0f * 10.0f)) < 1e-6f);
                assert(fabs(Iss[10] - (11.0f * 11.0f)) < 1e-6f);

                // Check PML boundaries remain unchanged
                assert(Isg[0] == 0.0f);
                assert(Isg[3] == 0.0f);
                assert(Isg[12] == 0.0f);
                assert(Isg[15] == 0.0f);
                assert(Iss[0] == 0.0f);
                assert(Iss[3] == 0.0f);
                assert(Iss[12] == 0.0f);
                assert(Iss[15] == 0.0f);
            }

            // Test Case 2: Edge case with npml = 0 (process all points)
            {
                const int npml = 0;
                const int nnz = 2;
                const int nnx = 2;
                float Isg[nnz * nnx] = {0};
                float Iss[nnz * nnx] = {0};
                float sp[nnz * nnx] = {1.0f, 2.0f, 3.0f, 4.0f};
                float gp[nnz * nnx] = {0.1f, 0.2f, 0.3f, 0.4f};

                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);

                for (int i = 0; i < nnz * nnx; ++i) {
                    assert(fabs(Isg[i] - (sp[i] * gp[i])) < 1e-6f);
                    assert(fabs(Iss[i] - (sp[i] * sp[i])) < 1e-6f);
                }
            }

            // Test Case 3: Large PML that leaves no inner points
            {
                const int npml = 2;
                const int nnz = 4;
                const int nnx = 4;
                float Isg[nnz * nnx] = {0};
                float Iss[nnz * nnx] = {0};
                float sp[nnz * nnx] = {1.0f};
                float gp[nnz * nnx] = {1.0f};

                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);

                // All points should remain unchanged
                for (int i = 0; i < nnz * nnx; ++i) {
                    assert(Isg[i] == 0.0f);
                    assert(Iss[i] == 0.0f);
                }
            }

            // Test Case 4: Different array sizes and values
            {
                const int npml = 1;
                const int nnz = 5;
                const int nnx = 3;
                float Isg[nnz * nnx] = {0};
                float Iss[nnz * nnx] = {0};
                float sp[nnz * nnx] = {0};
                float gp[nnz * nnx] = {0};

                // Fill arrays with some pattern
                for (int i = 0; i < nnz * nnx; ++i) {
                    sp[i] = i % 5 + 1.0f;
                    gp[i] = (i % 3 + 1) * 0.5f;
                }

                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);

                // Check inner points (1 <= i1 < 4, 1 <= i2 < 2)
                for (int i2 = 1; i2 < 2; ++i2) {
                    for (int i1 = 1; i1 < 4; ++i1) {
                        int id = i1 + i2 * nnz;
                        float expected_Isg = sp[id] * gp[id];
                        float expected_Iss = sp[id] * sp[id];
                        assert(fabs(Isg[id] - expected_Isg) < 1e-6f);
                        assert(fabs(Iss[id] - expected_Iss) < 1e-6f);
                    }
                }

                // Check PML boundaries remain unchanged
                for (int i2 = 0; i2 < nnx; ++i2) {
                    for (int i1 = 0; i1 < nnz; ++i1) {
                        if (i1 < npml || i1 >= nnz - npml || i2 < npml || i2 >= nnx - npml) {
                            int id = i1 + i2 * nnz;
                            assert(Isg[id] == 0.0f);
                            assert(Iss[id] == 0.0f);
                        }
                    }
                }
            }

            // Test Case 5: Accumulation check (call function multiple times)
            {
                const int npml = 1;
                const int nnz = 3;
                const int nnx = 3;
                float Isg[nnz * nnx] = {0};
                float Iss[nnz * nnx] = {0};
                float sp[nnz * nnx] = {1.0f, 2.0f, 3.0f,
                                       4.0f, 5.0f, 6.0f,
                                       7.0f, 8.0f, 9.0f};
                float gp[nnz * nnx] = {0.1f, 0.2f, 0.3f,
                                       0.4f, 0.5f, 0.6f,
                                       0.7f, 0.8f, 0.9f};

                // Call function twice
                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);
                cpu_cross_correlate(Isg, Iss, sp, gp, npml, nnz, nnx);

                // Only center point should be processed (id = 4)
                int id = 4;
                float expected_Isg = 2 * (sp[id] * gp[id]);
                float expected_Iss = 2 * (sp[id] * sp[id]);
                assert(fabs(Isg[id] - expected_Isg) < 1e-6f);
                assert(fabs(Iss[id] - expected_Iss) < 1e-6f);

                // All other points should remain unchanged
                for (int i = 0; i < nnz * nnx; ++i) {
                    if (i != id) {
                        assert(Isg[i] == 0.0f);
                        assert(Iss[i] == 0.0f);
                    }
                }
            }

            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }

        void cpu_cross_correlate(float* Isg, float* Iss, float* sp, float* gp, int npml, int nnz, int nnx) {
            for (int i2 = npml; i2 < nnx - npml; ++i2) {
                for (int i1 = npml; i1 < nnz - npml; ++i1) {
                    int id = i1 + i2 * nnz;
                    float ps = sp[id];
                    float pg = gp[id];
                    Isg[id] += ps * pg;
                    Iss[id] += ps * ps;
                }
            }
        }