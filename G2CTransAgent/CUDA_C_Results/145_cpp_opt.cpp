// Optimized code(id = 145): 

#include <iostream>

void waterElevationToDepth(int nx_, int ny_, float* h_ptr_, int h_pitch_, float* Bm_ptr_, int Bm_pitch_) {
    for (int tj = 0; tj < ny_; ++tj) {
        for (int ti = 0; ti < nx_; ++ti) {
            float* const h_row = reinterpret_cast<float*>(reinterpret_cast<char*>(h_ptr_) + h_pitch_ * tj);
            float* const Bm_row = reinterpret_cast<float*>(reinterpret_cast<char*>(Bm_ptr_) + Bm_pitch_ * tj);
            h_row[ti] -= Bm_row[ti];
        }
    }
}

// Example usage (not part of the translation)
/*
int main() {
    const int nx = 100;
    const int ny = 100;
    float* h = new float[nx * ny];
    float* Bm = new float[nx * ny];
    
    // Initialize arrays h and Bm with some values
    
    waterElevationToDepth(nx, ny, h, nx * sizeof(float), Bm, nx * sizeof(float));
    
    // Use the modified h array
    
    delete[] h;
    delete[] Bm;
    return 0;
}
*/