// original code(id = 52): 
 /*
__global__ void init_image_array_GPU ( unsigned long long int * image , int pixels_per_image ) { int my_pixel = threadIdx . x + blockIdx . x * blockDim . x ; if ( my_pixel < pixels_per_image ) { image [ my_pixel ] = ( unsigned long long int ) ( 0 ) ; my_pixel += pixels_per_image ; image [ my_pixel ] = ( unsigned long long int ) ( 0 ) ; my_pixel += pixels_per_image ; image [ my_pixel ] = ( unsigned long long int ) ( 0 ) ; my_pixel += pixels_per_image ; image [ my_pixel ] = ( unsigned long long int ) ( 0 ) ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void init_image_array_CPU(unsigned long long int* image, int pixels_per_image) {
            for (int my_pixel = 0; my_pixel < pixels_per_image; ++my_pixel) {
                image[my_pixel] = 0;
                image[my_pixel + pixels_per_image] = 0;
                image[my_pixel + 2 * pixels_per_image] = 0;
                image[my_pixel + 3 * pixels_per_image] = 0;
            }
        }

        void test_init_image_array_CPU() {
            // Test case 1: pixels_per_image = 0
            {
                unsigned long long int image[1] = {1}; // Dummy value
                init_image_array_CPU(image, 0);
                // No assertion needed as loop won't execute
            }

            // Test case 2: pixels_per_image = 1
            {
                unsigned long long int image[4] = {1, 1, 1, 1};
                init_image_array_CPU(image, 1);
                assert(image[0] == 0);
                assert(image[1] == 0);
                assert(image[2] == 0);
                assert(image[3] == 0);
            }

            // Test case 3: pixels_per_image = 100
            {
                const int pixels_per_image = 100;
                unsigned long long int image[4 * pixels_per_image];
                for (int i = 0; i < 4 * pixels_per_image; ++i) {
                    image[i] = i + 1; // Fill with non-zero values
                }
                init_image_array_CPU(image, pixels_per_image);
                for (int i = 0; i < 4 * pixels_per_image; ++i) {
                    assert(image[i] == 0);
                }
            }
        }

        int main() {
            test_init_image_array_CPU();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }