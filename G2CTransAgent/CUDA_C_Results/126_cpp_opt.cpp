// Optimized code(id = 126): 

void opL21(float* vec, float* vec1, long depth, long rows, long cols) {
            for (unsigned long z = 0; z < depth; ++z) {
                for (unsigned long y = 0; y < rows; ++y) {
                    for (unsigned long x = 0; x < cols; ++x) {
                        unsigned long long i = z * rows * cols + y * cols + x;
                        unsigned long long j = z * rows * cols + x;
                        unsigned long size2d = cols;
                        unsigned long size3d = depth * rows * cols + rows * cols + cols;
                        
                        if (i + cols + 1 < size3d) {
                            vec[i + cols] = 0.25f * (vec1[i + 1] + vec1[i] + vec1[i + cols + 1] + vec1[i + cols]);
                        }
                        
                        if (j + 1 < size2d) {
                            vec[j] = (vec1[j] + vec1[j + 1]) / 4.0f;
                        }
                    }
                }
            }
        }