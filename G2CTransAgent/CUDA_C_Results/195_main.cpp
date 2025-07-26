// original code(id = 195): 
 /*
__global__ void mean_kernel ( float * x , int batch , int filters , int spatial , float * mean ) { float scale = 1.f / ( batch * spatial ) ; int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i >= filters ) return ; int j , k ; mean [ i ] = 0 ; for ( j = 0 ; j < batch ; ++ j ) { for ( k = 0 ; k < spatial ; ++ k ) { int index = j * filters * spatial + i * spatial + k ; mean [ i ] += x [ index ] ; } } mean [ i ] *= scale ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cmath>

        void mean_kernel(float* x, int batch, int filters, int spatial, float* mean);

        int main() {
            // Test case 1: Normal case with small values
            {
                float x[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                int batch = 2;
                int filters = 2;
                int spatial = 2;
                float mean[2] = {0};
                
                mean_kernel(x, batch, filters, spatial, mean);
                
                assert(fabs(mean[0] - (1.0f + 2.0f + 5.0f + 6.0f) / 4.0f) < 1e-6f);
                assert(fabs(mean[1] - (3.0f + 4.0f + 7.0f + 8.0f) / 4.0f) < 1e-6f);
            }

            // Test case 2: Edge case with single batch and single spatial
            {
                float x[] = {1.0f, 2.0f};
                int batch = 1;
                int filters = 2;
                int spatial = 1;
                float mean[2] = {0};
                
                mean_kernel(x, batch, filters, spatial, mean);
                
                assert(fabs(mean[0] - 1.0f) < 1e-6f);
                assert(fabs(mean[1] - 2.0f) < 1e-6f);
            }

            // Test case 3: Edge case with zero values
            {
                float x[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
                int batch = 2;
                int filters = 2;
                int spatial = 2;
                float mean[2] = {0};
                
                mean_kernel(x, batch, filters, spatial, mean);
                
                assert(fabs(mean[0]) < 1e-6f);
                assert(fabs(mean[1]) < 1e-6f);
            }

            // Test case 4: Normal case with larger dimensions
            {
                float x[24];
                for (int i = 0; i < 24; ++i) {
                    x[i] = static_cast<float>(i + 1);
                }
                int batch = 3;
                int filters = 4;
                int spatial = 2;
                float mean[4] = {0};
                
                mean_kernel(x, batch, filters, spatial, mean);
                
                // Calculate expected means manually
                float expected[4] = {0};
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 2; ++k) {
                            int index = j * 4 * 2 + i * 2 + k;
                            expected[i] += x[index];
                        }
                    }
                    expected[i] /= (3 * 2);
                }
                
                for (int i = 0; i < 4; ++i) {
                    assert(fabs(mean[i] - expected[i]) < 1e-6f);
                }
            }

            // Test case 5: Invalid case with zero filters (should not crash)
            {
                float x[] = {1.0f, 2.0f};
                int batch = 1;
                int filters = 0;
                int spatial = 1;
                float mean[1] = {0};
                
                mean_kernel(x, batch, filters, spatial, mean);
                // No assertion as we just check it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void mean_kernel(float* x, int batch, int filters, int spatial, float* mean) {
            float scale = 1.f / (batch * spatial);
            for (int i = 0; i < filters; ++i) {
                mean[i] = 0;
                for (int j = 0; j < batch; ++j) {
                    for (int k = 0; k < spatial; ++k) {
                        int index = j * filters * spatial + i * spatial + k;
                        mean[i] += x[index];
                    }
                }
                mean[i] *= scale;
            }
        }