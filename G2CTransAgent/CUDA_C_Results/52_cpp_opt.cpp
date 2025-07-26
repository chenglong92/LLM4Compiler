// Optimized code(id = 52): 

void init_image_array_CPU(unsigned long long int* image, int pixels_per_image) {
            for (int my_pixel = 0; my_pixel < pixels_per_image; ++my_pixel) {
                image[my_pixel] = 0;
                image[my_pixel + pixels_per_image] = 0;
                image[my_pixel + 2 * pixels_per_image] = 0;
                image[my_pixel + 3 * pixels_per_image] = 0;
            }
        }