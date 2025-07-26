// original code(id = 101): 
 /*
__global__ void l1_kernel ( int n , float * pred , float * truth , float * delta , float * error ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < n ) { float diff = truth [ i ] - pred [ i ] ; error [ i ] = abs ( diff ) ; delta [ i ] = ( diff > 0 ) ? 1 : -1 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void l1_kernel(int n, float* pred, float* truth, float* delta, float* error);

        int main() {
            // Test case 1: Single element with positive difference
            {
                int n = 1;
                float pred[] = {1.0f};
                float truth[] = {3.0f};
                float delta[n];
                float error[n];
                
                l1_kernel(n, pred, truth, delta, error);
                
                assert(error[0] == 2.0f);
                assert(delta[0] == 1.0f);
            }

            // Test case 2: Single element with negative difference
            {
                int n = 1;
                float pred[] = {4.0f};
                float truth[] = {1.0f};
                float delta[n];
                float error[n];
                
                l1_kernel(n, pred, truth, delta, error);
                
                assert(error[0] == 3.0f);
                assert(delta[0] == -1.0f);
            }

            // Test case 3: Single element with zero difference
            {
                int n = 1;
                float pred[] = {2.5f};
                float truth[] = {2.5f};
                float delta[n];
                float error[n];
                
                l1_kernel(n, pred, truth, delta, error);
                
                assert(error[0] == 0.0f);
                assert(delta[0] == -1.0f);  // Note: (0 > 0) is false, so -1.0
            }

            // Test case 4: Multiple elements with mixed differences
            {
                int n = 4;
                float pred[] = {1.0f, 2.0f, 3.0f, 4.0f};
                float truth[] = {1.5f, 1.5f, 3.0f, 5.0f};
                float delta[n];
                float error[n];
                
                l1_kernel(n, pred, truth, delta, error);
                
                assert(error[0] == 0.5f);
                assert(delta[0] == 1.0f);
                assert(error[1] == 0.5f);
                assert(delta[1] == -1.0f);
                assert(error[2] == 0.0f);
                assert(delta[2] == -1.0f);
                assert(error[3] == 1.0f);
                assert(delta[3] == 1.0f);
            }

            // Test case 5: Empty array (should handle gracefully)
            {
                int n = 0;
                float* pred = nullptr;
                float* truth = nullptr;
                float delta[1];  // Dummy, won't be accessed
                float error[1];  // Dummy, won't be accessed
                
                l1_kernel(n, pred, truth, delta, error);
                // No assertions, just checking it doesn't crash
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void l1_kernel(int n, float* pred, float* truth, float* delta, float* error) {
            for (int i = 0; i < n; ++i) {
                float diff = truth[i] - pred[i];
                error[i] = abs(diff);
                delta[i] = (diff > 0) ? 1.0f : -1.0f;
            }
        }