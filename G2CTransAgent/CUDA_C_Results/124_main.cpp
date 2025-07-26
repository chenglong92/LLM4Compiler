// original code(id = 124): 
 /*
__global__ void primal_descent ( float * y1 , float * y2 , float * xbar , float sigma , int w , int h , int nc ) { int x = threadIdx . x + blockDim . x * blockIdx . x ; int y = threadIdx . y + blockDim . y * blockIdx . y ; if ( x < w && y < h ) { int i ; float x1 , x2 , val , norm ; for ( int z = 0 ; z < nc ; z ++ ) { i = x + w * y + w * h * z ; val = xbar [ i ] ; x1 = ( x + 1 < w ) ? ( xbar [ ( x + 1 ) + w * y + w * h * z ] - val ) : 0.f ; x2 = ( y + 1 < h ) ? ( xbar [ x + w * ( y + 1 ) + w * h * z ] - val ) : 0.f ; x1 = y1 [ i ] + sigma * x1 ; x2 = y2 [ i ] + sigma * x2 ; norm = sqrtf ( x1 * x1 + x2 * x2 ) ; y1 [ i ] = x1 / fmax ( 1.f , norm ) ; y2 [ i ] = x2 / fmax ( 1.f , norm ) ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cstdlib>

        void primal_descent(float* y1, float* y2, float* xbar, float sigma, int w, int h, int nc);

        int main() {
            // Test case 1: Small 2x2 single channel array
            {
                const int w = 2, h = 2, nc = 1;
                float y1[w*h*nc] = {0};
                float y2[w*h*nc] = {0};
                float xbar[w*h*nc] = {1.0f, 2.0f, 3.0f, 4.0f};
                float sigma = 0.5f;

                primal_descent(y1, y2, xbar, sigma, w, h, nc);

                std::cout << "Test case 1 results:" << std::endl;
                for (int i = 0; i < w*h*nc; ++i) {
                    std::cout << "y1[" << i << "] = " << y1[i] << ", y2[" << i << "] = " << y2[i] << std::endl;
                }
                std::cout << std::endl;
            }

            // Test case 2: Boundary conditions (3x1 single channel)
            {
                const int w = 3, h = 1, nc = 1;
                float y1[w*h*nc] = {0.1f, 0.2f, 0.3f};
                float y2[w*h*nc] = {0.4f, 0.5f, 0.6f};
                float xbar[w*h*nc] = {5.0f, 10.0f, 15.0f};
                float sigma = 1.0f;

                primal_descent(y1, y2, xbar, sigma, w, h, nc);

                std::cout << "Test case 2 results:" << std::endl;
                for (int i = 0; i < w*h*nc; ++i) {
                    std::cout << "y1[" << i << "] = " << y1[i] << ", y2[" << i << "] = " << y2[i] << std::endl;
                }
                std::cout << std::endl;
            }

            // Test case 3: Multiple channels (2x2x2)
            {
                const int w = 2, h = 2, nc = 2;
                float y1[w*h*nc] = {0};
                float y2[w*h*nc] = {0};
                float xbar[w*h*nc] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                float sigma = 0.1f;

                primal_descent(y1, y2, xbar, sigma, w, h, nc);

                std::cout << "Test case 3 results:" << std::endl;
                for (int i = 0; i < w*h*nc; ++i) {
                    std::cout << "y1[" << i << "] = " << y1[i] << ", y2[" << i << "] = " << y2[i] << std::endl;
                }
                std::cout << std::endl;
            }

            // Test case 4: Large sigma value
            {
                const int w = 1, h = 3, nc = 1;
                float y1[w*h*nc] = {0.5f, 0.5f, 0.5f};
                float y2[w*h*nc] = {0.5f, 0.5f, 0.5f};
                float xbar[w*h*nc] = {0.1f, 0.2f, 0.3f};
                float sigma = 100.0f;

                primal_descent(y1, y2, xbar, sigma, w, h, nc);

                std::cout << "Test case 4 results:" << std::endl;
                for (int i = 0; i < w*h*nc; ++i) {
                    std::cout << "y1[" << i << "] = " << y1[i] << ", y2[" << i << "] = " << y2[i] << std::endl;
                }
                std::cout << std::endl;
            }

            // Test case 5: Single element array
            {
                const int w = 1, h = 1, nc = 1;
                float y1[w*h*nc] = {0.8f};
                float y2[w*h*nc] = {0.9f};
                float xbar[w*h*nc] = {10.0f};
                float sigma = 0.5f;

                primal_descent(y1, y2, xbar, sigma, w, h, nc);

                std::cout << "Test case 5 results:" << std::endl;
                for (int i = 0; i < w*h*nc; ++i) {
                    std::cout << "y1[" << i << "] = " << y1[i] << ", y2[" << i << "] = " << y2[i] << std::endl;
                }
                std::cout << std::endl;
            }

            return 0;
        }

        void primal_descent(float* y1, float* y2, float* xbar, float sigma, int w, int h, int nc) {
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    for (int z = 0; z < nc; ++z) {
                        int i = x + w * y + w * h * z;
                        float val = xbar[i];
                        float x1 = (x + 1 < w) ? (xbar[(x + 1) + w * y + w * h * z] - val) : 0.f;
                        float x2 = (y + 1 < h) ? (xbar[x + w * (y + 1) + w * h * z] - val) : 0.f;
                        x1 = y1[i] + sigma * x1;
                        x2 = y2[i] + sigma * x2;
                        float norm = sqrtf(x1 * x1 + x2 * x2);
                        y1[i] = x1 / fmax(1.f, norm);
                        y2[i] = x2 / fmax(1.f, norm);
                    }
                }
            }
        }