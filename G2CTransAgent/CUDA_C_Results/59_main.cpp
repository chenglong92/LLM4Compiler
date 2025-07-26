// original code(id = 59): 
 /*
__global__ void shortcut_kernel ( int size , int minw , int minh , int minc , int stride , int sample , int batch , int w1 , int h1 , int c1 , float * add , int w2 , int h2 , int c2 , float * out ) { int id = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( id >= size ) return ; int i = id % minw ; id /= minw ; int j = id % minh ; id /= minh ; int k = id % minc ; id /= minc ; int b = id % batch ; int out_index = i * sample + w2 * ( j * sample + h2 * ( k + c2 * b ) ) ; int add_index = i * stride + w1 * ( j * stride + h1 * ( k + c1 * b ) ) ; out [ out_index ] += add [ add_index ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstdlib>
        #include <ctime>

        void shortcut_kernel(int size, int minw, int minh, int minc, int stride, int sample, int batch, int w1, int h1, int c1, float* add, int w2, int h2, int c2, float* out) {
            for (int id = 0; id < size; ++id) {
                int i = id % minw;
                id /= minw;
                int j = id % minh;
                id /= minh;
                int k = id % minc;
                id /= minc;
                int b = id % batch;
                
                int out_index = i * sample + w2 * (j * sample + h2 * (k + c2 * b));
                int add_index = i * stride + w1 * (j * stride + h1 * (k + c1 * b));
                
                out[out_index] += add[add_index];
                
                // Restore id for the next iteration
                id = (b * minc + k) * minh + j;
                id = id * minw + i;
            }
        }

        void test_shortcut_kernel() {
            // Test case 1: Small size with all dimensions equal to 1
            {
                const int size = 1;
                const int minw = 1, minh = 1, minc = 1, batch = 1;
                const int stride = 1, sample = 1;
                const int w1 = 1, h1 = 1, c1 = 1;
                const int w2 = 1, h2 = 1, c2 = 1;
                
                float add[size] = {5.0f};
                float out[size] = {0.0f};
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                assert(out[0] == 5.0f);
            }
            
            // Test case 2: Multiple batches
            {
                const int size = 4;
                const int minw = 1, minh = 1, minc = 1, batch = 4;
                const int stride = 1, sample = 1;
                const int w1 = 1, h1 = 1, c1 = 1;
                const int w2 = 1, h2 = 1, c2 = 1;
                
                float add[size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float out[size] = {0.0f};
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                for (int i = 0; i < size; ++i) {
                    assert(out[i] == add[i]);
                }
            }
            
            // Test case 3: Multiple channels
            {
                const int size = 4;
                const int minw = 1, minh = 1, minc = 4, batch = 1;
                const int stride = 1, sample = 1;
                const int w1 = 1, h1 = 1, c1 = 4;
                const int w2 = 1, h2 = 1, c2 = 4;
                
                float add[size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float out[size] = {0.0f};
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                for (int i = 0; i < size; ++i) {
                    assert(out[i] == add[i]);
                }
            }
            
            // Test case 4: Multiple height and width
            {
                const int size = 4;
                const int minw = 2, minh = 2, minc = 1, batch = 1;
                const int stride = 1, sample = 1;
                const int w1 = 2, h1 = 2, c1 = 1;
                const int w2 = 2, h2 = 2, c2 = 1;
                
                float add[size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float out[size] = {0.0f};
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                for (int i = 0; i < size; ++i) {
                    assert(out[i] == add[i]);
                }
            }
            
            // Test case 5: Different stride and sample values
            {
                const int size = 4;
                const int minw = 2, minh = 2, minc = 1, batch = 1;
                const int stride = 2, sample = 2;
                const int w1 = 4, h1 = 4, c1 = 1;
                const int w2 = 4, h2 = 4, c2 = 1;
                
                float add[size] = {1.0f, 2.0f, 3.0f, 4.0f};
                float out[16] = {0.0f}; // 4x4 output
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                assert(out[0] == 1.0f);
                assert(out[2] == 2.0f);
                assert(out[8] == 3.0f);
                assert(out[10] == 4.0f);
            }
            
            // Test case 6: Random values with larger dimensions
            {
                const int minw = 3, minh = 3, minc = 2, batch = 2;
                const int size = minw * minh * minc * batch;
                const int stride = 2, sample = 2;
                const int w1 = 6, h1 = 6, c1 = 2;
                const int w2 = 6, h2 = 6, c2 = 2;
                
                float* add = new float[size];
                float* out = new float[w2 * h2 * c2 * batch];
                
                std::srand(std::time(0));
                for (int i = 0; i < size; ++i) {
                    add[i] = static_cast<float>(std::rand() % 100);
                }
                for (int i = 0; i < w2 * h2 * c2 * batch; ++i) {
                    out[i] = 0.0f;
                }
                
                shortcut_kernel(size, minw, minh, minc, stride, sample, batch, w1, h1, c1, add, w2, h2, c2, out);
                
                // Verify some random indices
                int b = 1, k = 1, j = 1, i = 1;
                int out_index = i * sample + w2 * (j * sample + h2 * (k + c2 * b));
                int add_index = i * stride + w1 * (j * stride + h1 * (k + c1 * b));
                assert(out[out_index] == add[add_index]);
                
                b = 0, k = 0, j = 2, i = 1;
                out_index = i * sample + w2 * (j * sample + h2 * (k + c2 * b));
                add_index = i * stride + w1 * (j * stride + h1 * (k + c1 * b));
                assert(out[out_index] == add[add_index]);
                
                delete[] add;
                delete[] out;
            }
        }

        int main() {
            test_shortcut_kernel();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }