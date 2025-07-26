// Optimized code(id = 137): 

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