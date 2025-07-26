// Optimized code(id = 99): 

void evenoddincrement(float* g_data, int size, int even_inc, int odd_inc) {
    for (int tx = 0; tx < size; ++tx) {
        if ((tx % 2) == 0) {
            g_data[tx] += even_inc;
        } else {
            g_data[tx] += odd_inc;
        }
    }
}