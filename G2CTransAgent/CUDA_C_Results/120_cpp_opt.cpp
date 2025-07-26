// Optimized code(id = 120): 

void kernelIsFirst(int* head, int* first_pts, int n) {
    for (int i = 0; i < n; ++i) {
        if (head[i] == 1) {
            first_pts[i] = i;
        } else {
            first_pts[i] = 0;
        }
    }
}