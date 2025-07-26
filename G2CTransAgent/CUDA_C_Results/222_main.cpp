// original code(id = 222): 
 /*
__global__ void cuda_Adam_step_kernel ( float * grad , float * data , float * m , float * v , bool decay , float weight_decay , float beta1 , float beta2 , float eps , float step_size , int varsize ) { int i = blockIdx . x * blockDim . x + threadIdx . x ; if ( i >= varsize ) return ; float g = grad [ i ] ; if ( decay ) g += weight_decay * data [ i ] ; m [ i ] = beta1 * m [ i ] + ( 1.0 - beta1 ) * g ; v [ i ] = beta2 * v [ i ] + ( 1.0 - beta2 ) * g * g ; data [ i ] -= step_size * m [ i ] / ( sqrtf ( v [ i ] ) + eps ) ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cstdlib>
        #include <cassert>

        void cuda_Adam_step_kernel(float* grad, float* data, float* m, float* v, bool decay, float weight_decay, float beta1, float beta2, float eps, float step_size, int varsize);

        void test_adam_step() {
            // Test case 1: Basic case without decay
            {
                const int size = 5;
                float grad[size] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f};
                float data[size] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
                float m[size] = {0.0f};
                float v[size] = {0.0f};
                
                cuda_Adam_step_kernel(grad, data, m, v, false, 0.0f, 0.9f, 0.999f, 1e-8f, 0.001f, size);
                
                for (int i = 0; i < size; ++i) {
                    float expected_m = 0.9f * 0.0f + 0.1f * grad[i];
                    float expected_v = 0.999f * 0.0f + 0.001f * grad[i] * grad[i];
                    float expected_data = data[i] + grad[i]; // initial value before subtraction
                    expected_data -= 0.001f * expected_m / (sqrtf(expected_v) + 1e-8f);
                    
                    assert(fabs(m[i] - expected_m) < 1e-6f);
                    assert(fabs(v[i] - expected_v) < 1e-6f);
                    assert(fabs(data[i] - expected_data) < 1e-6f);
                }
            }
            
            // Test case 2: With weight decay
            {
                const int size = 3;
                float grad[size] = {-0.1f, 0.0f, 0.1f};
                float data[size] = {0.5f, 1.0f, 1.5f};
                float m[size] = {0.1f, 0.2f, 0.3f};
                float v[size] = {0.01f, 0.02f, 0.03f};
                float weight_decay = 0.01f;
                
                cuda_Adam_step_kernel(grad, data, m, v, true, weight_decay, 0.9f, 0.999f, 1e-8f, 0.01f, size);
                
                for (int i = 0; i < size; ++i) {
                    float expected_g = grad[i] + weight_decay * data[i];
                    float expected_m = 0.9f * m[i] + 0.1f * expected_g;
                    float expected_v = 0.999f * v[i] + 0.001f * expected_g * expected_g;
                    float expected_data = data[i] + expected_g; // initial value before subtraction
                    expected_data -= 0.01f * expected_m / (sqrtf(expected_v) + 1e-8f);
                    
                    assert(fabs(m[i] - expected_m) < 1e-6f);
                    assert(fabs(v[i] - expected_v) < 1e-6f);
                    assert(fabs(data[i] - expected_data) < 1e-6f);
                }
            }
            
            // Test case 3: Edge case with zero gradients
            {
                const int size = 4;
                float grad[size] = {0.0f};
                float data[size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float m[size] = {0.5f, 0.5f, 0.5f, 0.5f};
                float v[size] = {0.25f, 0.25f, 0.25f, 0.25f};
                
                cuda_Adam_step_kernel(grad, data, m, v, false, 0.0f, 0.9f, 0.999f, 1e-8f, 0.1f, size);
                
                for (int i = 0; i < size; ++i) {
                    float expected_m = 0.9f * m[i];
                    float expected_v = 0.999f * v[i];
                    float expected_data = data[i] - 0.1f * expected_m / (sqrtf(expected_v) + 1e-8f);
                    
                    assert(fabs(m[i] - expected_m) < 1e-6f);
                    assert(fabs(v[i] - expected_v) < 1e-6f);
                    assert(fabs(data[i] - expected_data) < 1e-6f);
                }
            }
            
            // Test case 4: Single element array
            {
                const int size = 1;
                float grad[size] = {0.5f};
                float data[size] = {10.0f};
                float m[size] = {0.0f};
                float v[size] = {0.0f};
                
                cuda_Adam_step_kernel(grad, data, m, v, true, 0.1f, 0.95f, 0.99f, 1e-7f, 0.01f, size);
                
                float expected_g = grad[0] + 0.1f * data[0];
                float expected_m = 0.95f * m[0] + 0.05f * expected_g;
                float expected_v = 0.99f * v[0] + 0.01f * expected_g * expected_g;
                float expected_data = data[0] + expected_g; // initial value before subtraction
                expected_data -= 0.01f * expected_m / (sqrtf(expected_v) + 1e-7f);
                
                assert(fabs(m[0] - expected_m) < 1e-6f);
                assert(fabs(v[0] - expected_v) < 1e-6f);
                assert(fabs(data[0] - expected_data) < 1e-6f);
            }
            
            // Test case 5: Different beta values
            {
                const int size = 2;
                float grad[size] = {0.3f, -0.2f};
                float data[size] = {5.0f, 10.0f};
                float m[size] = {0.1f, 0.2f};
                float v[size] = {0.1f, 0.2f};
                float beta1 = 0.8f;
                float beta2 = 0.9f;
                
                cuda_Adam_step_kernel(grad, data, m, v, false, 0.0f, beta1, beta2, 1e-6f, 0.05f, size);
                
                for (int i = 0; i < size; ++i) {
                    float expected_m = beta1 * m[i] + (1.0f - beta1) * grad[i];
                    float expected_v = beta2 * v[i] + (1.0f - beta2) * grad[i] * grad[i];
                    float expected_data = data[i] + grad[i]; // initial value before subtraction
                    expected_data -= 0.05f * expected_m / (sqrtf(expected_v) + 1e-6f);
                    
                    assert(fabs(m[i] - expected_m) < 1e-6f);
                    assert(fabs(v[i] - expected_v) < 1e-6f);
                    assert(fabs(data[i] - expected_data) < 1e-6f);
                }
            }
        }

        int main() {
            test_adam_step();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }