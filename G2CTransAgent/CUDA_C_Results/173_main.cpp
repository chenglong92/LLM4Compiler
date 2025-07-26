// original code(id = 173): 
 /*
__global__ void kernel_CEE ( float * x , int * t , float * loss , int r , int c ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; int N = r ; float temp ; while ( i < N ) { for ( int j = 0 ; j < c ; j ++ ) { if ( t [ i * c + j ] == 1 ) { temp = logf ( x [ i * c + j ] + 1e-7 ) ; atomicAdd ( loss , temp ) ; continue ; } } i += gridDim . x * blockDim . x ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

void kernel_CEE(float* x, int* t, float* loss, int r, int c) {
    int N = r;
    float temp;
    *loss = 0.0f; // Initialize loss
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < c; ++j) {
            if (t[i * c + j] == 1) {
                temp = logf(x[i * c + j] + 1e-7f);
                *loss += temp;
                break; // Assuming one-hot encoding (only one '1' per row)
            }
        }
    }
}

int main() {
    // Test Case 1: Basic test with one-hot encoding
    {
        const int r = 3;
        const int c = 4;
        float x[r * c] = {0.1f, 0.2f, 0.3f, 0.4f,
                          0.5f, 0.1f, 0.2f, 0.2f,
                          0.3f, 0.3f, 0.3f, 0.1f};
        int t[r * c] = {0, 1, 0, 0,
                        1, 0, 0, 0,
                        0, 0, 0, 1};
        float loss;
        
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 1 - Loss: " << loss << std::endl;
    }
    
    // Test Case 2: All zeros in target (invalid one-hot)
    {
        const int r = 2;
        const int c = 3;
        float x[r * c] = {0.5f, 0.3f, 0.2f,
                          0.1f, 0.7f, 0.2f};
        int t[r * c] = {0, 0, 0,
                        0, 0, 0};
        float loss;
        
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 2 - Loss: " << loss << std::endl;
    }
    
    // Test Case 3: Multiple 1s in a row (invalid one-hot)
    {
        const int r = 2;
        const int c = 3;
        float x[r * c] = {0.2f, 0.5f, 0.3f,
                          0.1f, 0.8f, 0.1f};
        int t[r * c] = {1, 1, 0,
                        0, 1, 1};
        float loss;
        
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 3 - Loss: " << loss << std::endl;
    }
    
    // Test Case 4: Single row with one-hot
    {
        const int r = 1;
        const int c = 5;
        float x[r * c] = {0.05f, 0.1f, 0.7f, 0.1f, 0.05f};
        int t[r * c] = {0, 0, 1, 0, 0};
        float loss;
        
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 4 - Loss: " << loss << std::endl;
    }
    
    // Test Case 5: Very small probabilities
    {
        const int r = 2;
        const int c = 2;
        float x[r * c] = {1e-8f, 1.0f - 1e-8f,
                          1.0f - 1e-8f, 1e-8f};
        int t[r * c] = {0, 1,
                        1, 0};
        float loss;
        
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 5 - Loss: " << loss << std::endl;
    }
    
    // Test Case 6: Random test
    {
        srand(time(0));
        const int r = 5;
        const int c = 4;
        float x[r * c];
        int t[r * c] = {0};
        
        // Generate random probabilities (normalized per row)
        for (int i = 0; i < r; ++i) {
            float sum = 0.0f;
            for (int j = 0; j < c; ++j) {
                x[i * c + j] = static_cast<float>(rand()) / RAND_MAX;
                sum += x[i * c + j];
            }
            // Normalize
            for (int j = 0; j < c; ++j) {
                x[i * c + j] /= sum;
            }
            // Set one-hot target
            int hot_pos = rand() % c;
            t[i * c + hot_pos] = 1;
        }
        
        float loss;
        kernel_CEE(x, t, &loss, r, c);
        std::cout << "Test Case 6 - Loss: " << loss << std::endl;
    }
    
    return 0;
}