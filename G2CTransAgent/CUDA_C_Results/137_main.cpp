// original code(id = 137): 
 /*
__global__ void waterDepthToElevation ( const int nx_ , const int ny_ , float * w_ptr_ , int w_pitch_ , float * h_ptr_ , int h_pitch_ , float * Bm_ptr_ , int Bm_pitch_ ) { const int ti = blockIdx . x * blockDim . x + threadIdx . x ; const int tj = blockIdx . y * blockDim . y + threadIdx . y ; if ( ti < nx_ && tj < ny_ ) { float * const h_row = ( float * ) ( ( char * ) h_ptr_ + h_pitch_ * tj ) ; float * const Bm_row = ( float * ) ( ( char * ) Bm_ptr_ + Bm_pitch_ * tj ) ; float * const w_row = ( float * ) ( ( char * ) w_ptr_ + w_pitch_ * tj ) ; w_row [ ti ] = h_row [ ti ] + Bm_row [ ti ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void waterDepthToElevation(const int nx_, const int ny_, float* w_ptr_, int w_pitch_, float* h_ptr_, int h_pitch_, float* Bm_ptr_, int Bm_pitch_) {
            for (int tj = 0; tj < ny_; ++tj) {
                for (int ti = 0; ti < nx_; ++ti) {
                    float* const h_row = reinterpret_cast<float*>(reinterpret_cast<char*>(h_ptr_) + h_pitch_ * tj);
                    float* const Bm_row = reinterpret_cast<float*>(reinterpret_cast<char*>(Bm_ptr_) + Bm_pitch_ * tj);
                    float* const w_row = reinterpret_cast<float*>(reinterpret_cast<char*>(w_ptr_) + w_pitch_ * tj);
                    w_row[ti] = h_row[ti] + Bm_row[ti];
                }
            }
        }

        int main() {
            // Test case 1: Basic functionality
            {
                const int nx = 3;
                const int ny = 2;
                float h_data[nx * ny] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
                float Bm_data[nx * ny] = {0.5f, 1.5f, 2.5f, 3.5f, 4.5f, 5.5f};
                float w_data[nx * ny] = {0.0f};

                waterDepthToElevation(nx, ny, w_data, nx * sizeof(float), h_data, nx * sizeof(float), Bm_data, nx * sizeof(float));

                for (int i = 0; i < nx * ny; ++i) {
                    assert(w_data[i] == h_data[i] + Bm_data[i]);
                }
            }

            // Test case 2: Single element
            {
                const int nx = 1;
                const int ny = 1;
                float h_data = 10.0f;
                float Bm_data = 20.0f;
                float w_data = 0.0f;

                waterDepthToElevation(nx, ny, &w_data, sizeof(float), &h_data, sizeof(float), &Bm_data, sizeof(float));

                assert(w_data == h_data + Bm_data);
            }

            // Test case 3: Empty grid (should do nothing)
            {
                const int nx = 0;
                const int ny = 0;
                float* h_data = nullptr;
                float* Bm_data = nullptr;
                float* w_data = nullptr;

                waterDepthToElevation(nx, ny, w_data, 0, h_data, 0, Bm_data, 0);
                // No assertion needed as it should just not crash
            }

            // Test case 4: Non-contiguous pitch
            {
                const int nx = 2;
                const int ny = 3;
                const int pitch = 4 * sizeof(float); // Extra space between rows
                float h_data[ny * pitch / sizeof(float)] = {1.0f, 2.0f, 0.0f, 0.0f, 3.0f, 4.0f, 0.0f, 0.0f, 5.0f, 6.0f, 0.0f, 0.0f};
                float Bm_data[ny * pitch / sizeof(float)] = {0.5f, 1.5f, 0.0f, 0.0f, 2.5f, 3.5f, 0.0f, 0.0f, 4.5f, 5.5f, 0.0f, 0.0f};
                float w_data[ny * pitch / sizeof(float)] = {0.0f};

                waterDepthToElevation(nx, ny, w_data, pitch, h_data, pitch, Bm_data, pitch);

                for (int j = 0; j < ny; ++j) {
                    for (int i = 0; i < nx; ++i) {
                        assert(w_data[j * pitch / sizeof(float) + i] == 
                               h_data[j * pitch / sizeof(float) + i] + 
                               Bm_data[j * pitch / sizeof(float) + i]);
                    }
                }
            }

            std::cout << "All tests passed!" << std::endl;
            return 0;
        }