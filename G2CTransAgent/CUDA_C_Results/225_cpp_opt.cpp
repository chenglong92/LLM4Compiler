// Optimized code(id = 225): 

void histogram(int n, int* color, int* bucket) {
            for (int i = 0; i < n; ++i) {
                int c = color[i];
                bucket[c] += 1;
            }
        }