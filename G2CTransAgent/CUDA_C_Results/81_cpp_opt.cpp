// Optimized code(id = 81): 

void MMDOuterProdComputeWithSum(float* x_average, int size_x, float* x_outer_prod) {
            for (int i = 0; i < size_x; ++i) {
                x_outer_prod[i] = x_average[i] * x_average[i];
            }
        }