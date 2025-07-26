// Optimized code(id = 189): 

void k_vec_divide(float* vec1, float* vec2, size_t max_size) {
            for (size_t i = 0; i < max_size; ++i) {
                vec1[i] = vec1[i] / vec2[i];
            }
        }