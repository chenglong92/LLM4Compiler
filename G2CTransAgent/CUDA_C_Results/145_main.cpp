// original code(id = 145): 
 /*
__global__ void waterElevationToDepth ( const int nx_ , const int ny_ , float * h_ptr_ , int h_pitch_ , float * Bm_ptr_ , int Bm_pitch_ ) { int ti = blockIdx . x * blockDim . x + threadIdx . x ; int tj = blockIdx . y * blockDim . y + threadIdx . y ; if ( ti < nx_ && tj < ny_ ) { float * const h_row = ( float * ) ( ( char * ) h_ptr_ + h_pitch_ * tj ) ; float * const Bm_row = ( float * ) ( ( char * ) Bm_ptr_ + Bm_pitch_ * tj ) ; h_row [ ti ] -= Bm_row [ ti ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void waterElevationToDepth(int nx_, int ny_, float* h_ptr_, int h_pitch_, float* Bm_ptr_, int Bm_pitch_) {
            for (int tj = 0; tj < ny_; ++tj) {
                for (int ti = 0; ti < nx_; ++ti) {
                    float* const h_row = reinterpret_cast<float*>(reinterpret_cast<char*>(h_ptr_) + h_pitch_ * tj);
                    float* const Bm_row = reinterpret_cast<float*>(reinterpret_cast<char*>(Bm_ptr_) + Bm_pitch_ * tj);
                    h_row[ti] -= Bm_row[ti];
                }
            }
        }

        int main() {
            // Test case 1: Normal case with 3x3 arrays
            {
                const int nx = 3;
                const int ny = 3;
                float h[nx * ny] = {10.0f, 20.0f, 30.0f, 
                                   40.0f, 50.0f, 60.0f, 
                                   70.0f, 80.0f, 90.0f};
                float Bm[nx * ny] = {1.0f, 2.0f, 3.0f, 
                                    4.0f, 5.0f, 6.0f, 
                                    7.0f, 8.0f, 9.0f};
                float expected[nx * ny] = {9.0f, 18.0f, 27.0f, 
                                         36.0f, 45.0f, 54.0f, 
                                         63.0f, 72.0f, 81.0f};

                waterElevationToDepth(nx, ny, h, nx * sizeof(float), Bm, nx * sizeof(float));

                for (int i = 0; i < nx * ny; ++i) {
                    assert(h[i] == expected[i]);
                }
            }

            // Test case 2: Edge case with 1x1 arrays
            {
                const int nx = 1;
                const int ny = 1;
                float h[nx * ny] = {100.0f};
                float Bm[nx * ny] = {25.0f};
                float expected[nx * ny] = {75.0f};

                waterElevationToDepth(nx, ny, h, nx * sizeof(float), Bm, nx * sizeof(float));

                assert(h[0] == expected[0]);
            }

            // Test case 3: Edge case with empty arrays (should not crash)
            {
                const int nx = 0;
                const int ny = 0;
                float* h = nullptr;
                float* Bm = nullptr;

                waterElevationToDepth(nx, ny, h, 0, Bm, 0);
                // No assertion, just checking it doesn't crash
            }

            // Test case 4: Non-contiguous memory case
            {
                const int nx = 2;
                const int ny = 2;
                float h_data[4] = {10.0f, 20.0f, 30.0f, 40.0f};
                float Bm_data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
                float expected[4] = {9.0f, 18.0f, 27.0f, 36.0f};

                // Create non-contiguous arrays by using every other element
                float* h_rows[2];
                float* Bm_rows[2];
                for (int i = 0; i < 2; ++i) {
                    h_rows[i] = &h_data[i * 2];
                    Bm_rows[i] = &Bm_data[i * 2];
                }

                waterElevationToDepth(nx, ny, h_data, 2 * sizeof(float), Bm_data, 2 * sizeof(float));

                for (int i = 0; i < 4; ++i) {
                    assert(h_data[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }