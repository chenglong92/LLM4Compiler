// original code(id = 132): 
 /*
__global__ void binarize_input_kernel ( float * input , int n , int size , float * binary ) { int s = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( s >= size ) return ; int i = 0 ; float mean = 0 ; for ( i = 0 ; i < n ; ++ i ) { mean += abs ( input [ i * size + s ] ) ; } mean = mean / n ; for ( i = 0 ; i < n ; ++ i ) { binary [ i * size + s ] = ( input [ i * size + s ] > 0 ) ? mean : - mean ; } }
*/
// optimized code: 

#include <cmath>
#include <iostream>
#include <cassert>

void binarize_input_kernel(float* input, int n, int size, float* binary);

void test_binarize_input_kernel() {
    // Test case 1: Basic test with positive and negative values
    {
        float input[] = {1.0f, -2.0f, 3.0f, -4.0f, 5.0f, -6.0f};
        float binary[6];
        int n = 3;
        int size = 2;
        
        binarize_input_kernel(input, n, size, binary);
        
        float expected_mean0 = (1.0f + 3.0f + 5.0f) / 3.0f;
        float expected_mean1 = (2.0f + 4.0f + 6.0f) / 3.0f;
        
        assert(binary[0] == expected_mean0);
        assert(binary[1] == -expected_mean1);
        assert(binary[2] == expected_mean0);
        assert(binary[3] == -expected_mean1);
        assert(binary[4] == expected_mean0);
        assert(binary[5] == -expected_mean1);
    }

    // Test case 2: All positive values
    {
        float input[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
        float binary[6];
        int n = 3;
        int size = 2;
        
        binarize_input_kernel(input, n, size, binary);
        
        float expected_mean0 = (1.0f + 3.0f + 5.0f) / 3.0f;
        float expected_mean1 = (2.0f + 4.0f + 6.0f) / 3.0f;
        
        assert(binary[0] == expected_mean0);
        assert(binary[1] == expected_mean1);
        assert(binary[2] == expected_mean0);
        assert(binary[3] == expected_mean1);
        assert(binary[4] == expected_mean0);
        assert(binary[5] == expected_mean1);
    }

    // Test case 3: All negative values
    {
        float input[] = {-1.0f, -2.0f, -3.0f, -4.0f, -5.0f, -6.0f};
        float binary[6];
        int n = 3;
        int size = 2;
        
        binarize_input_kernel(input, n, size, binary);
        
        float expected_mean0 = (1.0f + 3.0f + 5.0f) / 3.0f;
        float expected_mean1 = (2.0f + 4.0f + 6.0f) / 3.0f;
        
        assert(binary[0] == -expected_mean0);
        assert(binary[1] == -expected_mean1);
        assert(binary[2] == -expected_mean0);
        assert(binary[3] == -expected_mean1);
        assert(binary[4] == -expected_mean0);
        assert(binary[5] == -expected_mean1);
    }

    // Test case 4: Single element (n=1)
    {
        float input[] = {2.0f, -3.0f};
        float binary[2];
        int n = 1;
        int size = 2;
        
        binarize_input_kernel(input, n, size, binary);
        
        assert(binary[0] == 2.0f);
        assert(binary[1] == -3.0f);
    }

    // Test case 5: Large size
    {
        const int n = 100;
        const int size = 50;
        float input[n * size];
        float binary[n * size];
        
        for (int i = 0; i < n; ++i) {
            for (int s = 0; s < size; ++s) {
                input[i * size + s] = (i + s) % 2 == 0 ? 1.0f : -1.0f;
            }
        }
        
        binarize_input_kernel(input, n, size, binary);
        
        for (int s = 0; s < size; ++s) {
            float expected_mean = 1.0f;
            for (int i = 0; i < n; ++i) {
                if (input[i * size + s] > 0) {
                    assert(binary[i * size + s] == expected_mean);
                } else {
                    assert(binary[i * size + s] == -expected_mean);
                }
            }
        }
    }

    // Test case 6: All zeros
    {
        float input[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        float binary[6];
        int n = 3;
        int size = 2;
        
        binarize_input_kernel(input, n, size, binary);
        
        for (int i = 0; i < 6; ++i) {
            assert(binary[i] == 0.0f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    test_binarize_input_kernel();
    return 0;
}