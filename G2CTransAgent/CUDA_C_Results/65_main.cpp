// original code(id = 65): 
 /*
__global__ void variance_kernel ( float * x , float * mean , int batch , int filters , int spatial , float * variance ) { float scale = 1.f / ( batch * spatial - 1 ) ; int j , k ; int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i >= filters ) return ; variance [ i ] = 0 ; for ( j = 0 ; j < batch ; ++ j ) { for ( k = 0 ; k < spatial ; ++ k ) { int index = j * filters * spatial + i * spatial + k ; variance [ i ] += powf ( ( x [ index ] - mean [ i ] ) , 2 ) ; } } variance [ i ] *= scale ; }
*/
// optimized code: 

#include <cmath>
        #include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void variance_kernel(float* x, float* mean, int batch, int filters, int spatial, float* variance);

        int main() {
            // Test case 1: Simple case with batch=2, filters=2, spatial=2
            {
                float x[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                float mean[] = {2.5f, 6.5f};
                float variance[2] = {0};
                int batch = 2, filters = 2, spatial = 2;
                
                variance_kernel(x, mean, batch, filters, spatial, variance);
                
                float expected_variance0 = (std::pow(1.0f-2.5f, 2) + std::pow(2.0f-2.5f, 2) + 
                                          std::pow(5.0f-2.5f, 2) + std::pow(6.0f-2.5f, 2)) / 3.0f;
                float expected_variance1 = (std::pow(3.0f-6.5f, 2) + std::pow(4.0f-6.5f, 2) + 
                                          std::pow(7.0f-6.5f, 2) + std::pow(8.0f-6.5f, 2)) / 3.0f;
                
                assert(std::abs(variance[0] - expected_variance0) < 1e-6f);
                assert(std::abs(variance[1] - expected_variance1) < 1e-6f);
            }

            // Test case 2: Single batch, single filter, multiple spatial
            {
                float x[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float mean[] = {2.5f};
                float variance[1] = {0};
                int batch = 1, filters = 1, spatial = 4;
                
                variance_kernel(x, mean, batch, filters, spatial, variance);
                
                float expected_variance = (std::pow(1.0f-2.5f, 2) + std::pow(2.0f-2.5f, 2) + 
                                         std::pow(3.0f-2.5f, 2) + std::pow(4.0f-2.5f, 2)) / 3.0f;
                
                assert(std::abs(variance[0] - expected_variance) < 1e-6f);
            }

            // Test case 3: Multiple batches, single filter, single spatial
            {
                float x[] = {1.0f, 2.0f, 3.0f};
                float mean[] = {2.0f};
                float variance[1] = {0};
                int batch = 3, filters = 1, spatial = 1;
                
                variance_kernel(x, mean, batch, filters, spatial, variance);
                
                float expected_variance = (std::pow(1.0f-2.0f, 2) + std::pow(2.0f-2.0f, 2) + 
                                         std::pow(3.0f-2.0f, 2)) / 2.0f;
                
                assert(std::abs(variance[0] - expected_variance) < 1e-6f);
            }

            // Test case 4: Random values for larger dimensions
            {
                const int batch = 5, filters = 4, spatial = 3;
                float x[batch * filters * spatial];
                float mean[filters];
                float variance[filters] = {0};
                
                std::srand(std::time(0));
                for (int i = 0; i < filters; ++i) {
                    mean[i] = static_cast<float>(std::rand()) / RAND_MAX * 10.0f;
                }
                
                for (int j = 0; j < batch; ++j) {
                    for (int i = 0; i < filters; ++i) {
                        for (int k = 0; k < spatial; ++k) {
                            int index = j * filters * spatial + i * spatial + k;
                            x[index] = static_cast<float>(std::rand()) / RAND_MAX * 10.0f;
                        }
                    }
                }
                
                variance_kernel(x, mean, batch, filters, spatial, variance);
                
                // Manually calculate expected variance for each filter
                for (int i = 0; i < filters; ++i) {
                    float sum = 0.0f;
                    for (int j = 0; j < batch; ++j) {
                        for (int k = 0; k < spatial; ++k) {
                            int index = j * filters * spatial + i * spatial + k;
                            sum += std::pow(x[index] - mean[i], 2);
                        }
                    }
                    float expected_variance = sum / (batch * spatial - 1);
                    assert(std::abs(variance[i] - expected_variance) < 1e-6f);
                }
            }

            // Test case 5: Edge case with minimal dimensions (batch=1, filters=1, spatial=1)
            {
                float x[] = {1.0f};
                float mean[] = {1.0f};
                float variance[1] = {0};
                int batch = 1, filters = 1, spatial = 1;
                
                variance_kernel(x, mean, batch, filters, spatial, variance);
                
                // Variance should be 0 since there's only one sample
                assert(std::abs(variance[0] - 0.0f) < 1e-6f);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void variance_kernel(float* x, float* mean, int batch, int filters, int spatial, float* variance) {
            float scale = 1.f / (batch * spatial - 1);
            
            for (int i = 0; i < filters; ++i) {
                variance[i] = 0;
                
                for (int j = 0; j < batch; ++j) {
                    for (int k = 0; k < spatial; ++k) {
                        int index = j * filters * spatial + i * spatial + k;
                        variance[i] += std::pow((x[index] - mean[i]), 2);
                    }
                }
                
                variance[i] *= scale;
            }
        }