// original code(id = 119): 
 /*
__global__ void getMeanImage ( const double * images , double * meanImage , int imageNum , int pixelNum ) { int col = blockIdx . x * blockDim . x + threadIdx . x ; if ( col >= pixelNum ) { return ; } meanImage [ col ] = 0.0 ; for ( int row = 0 ; row < imageNum ; ++ row ) { meanImage [ col ] += images [ row * pixelNum + col ] ; } meanImage [ col ] /= imageNum ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void getMeanImage(const double* images, double* meanImage, int imageNum, int pixelNum);

        int main() {
            // Test case 1: Single image with single pixel
            {
                double images[] = {5.0};
                double meanImage[1];
                getMeanImage(images, meanImage, 1, 1);
                assert(meanImage[0] == 5.0);
            }

            // Test case 2: Multiple images with single pixel
            {
                double images[] = {1.0, 2.0, 3.0, 4.0};
                double meanImage[1];
                getMeanImage(images, meanImage, 4, 1);
                assert(meanImage[0] == 2.5);
            }

            // Test case 3: Single image with multiple pixels
            {
                double images[] = {1.0, 2.0, 3.0};
                double meanImage[3];
                getMeanImage(images, meanImage, 1, 3);
                assert(meanImage[0] == 1.0);
                assert(meanImage[1] == 2.0);
                assert(meanImage[2] == 3.0);
            }

            // Test case 4: Multiple images with multiple pixels
            {
                double images[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
                double meanImage[3];
                getMeanImage(images, meanImage, 2, 3);
                assert(meanImage[0] == 2.5);
                assert(meanImage[1] == 3.5);
                assert(meanImage[2] == 4.5);
            }

            // Test case 5: Zero images (should not crash)
            {
                double images[] = {1.0, 2.0, 3.0};
                double meanImage[3];
                getMeanImage(images, meanImage, 0, 3);
                // No assertion as behavior is undefined for zero images
            }

            // Test case 6: Zero pixels (should not crash)
            {
                double images[] = {1.0, 2.0, 3.0};
                double meanImage[0];
                getMeanImage(images, meanImage, 3, 0);
                // No assertion as behavior is undefined for zero pixels
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }