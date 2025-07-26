// original code(id = 215): 
 /*
__global__ void l2_kernel ( int n , float * pred , float * truth , float * delta , float * error ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < n ) { float diff = truth [ i ] - pred [ i ] ; error [ i ] = diff * diff ; delta [ i ] = diff ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void l2_kernel(int n, float* pred, float* truth, float* delta, float* error);

        int main() {
            // Test case 1: Basic test with positive values
            {
                const int n = 3;
                float pred[n] = {1.0f, 2.0f, 3.0f};
                float truth[n] = {2.0f, 3.0f, 4.0f};
                float delta[n];
                float error[n];

                l2_kernel(n, pred, truth, delta, error);

                for (int i = 0; i < n; ++i) {
                    float expected_diff = truth[i] - pred[i];
                    assert(delta[i] == expected_diff);
                    assert(error[i] == expected_diff * expected_diff);
                }
            }

            // Test case 2: Basic test with negative values
            {
                const int n = 3;
                float pred[n] = {-1.0f, -2.0f, -3.0f};
                float truth[n] = {-2.0f, -3.0f, -4.0f};
                float delta[n];
                float error[n];

                l2_kernel(n, pred, truth, delta, error);

                for (int i = 0; i < n; ++i) {
                    float expected_diff = truth[i] - pred[i];
                    assert(delta[i] == expected_diff);
                    assert(error[i] == expected_diff * expected_diff);
                }
            }

            // Test case 3: Mixed positive and negative values
            {
                const int n = 4;
                float pred[n] = {-1.0f, 2.0f, -3.0f, 4.0f};
                float truth[n] = {1.0f, -2.0f, 3.0f, -4.0f};
                float delta[n];
                float error[n];

                l2_kernel(n, pred, truth, delta, error);

                for (int i = 0; i < n; ++i) {
                    float expected_diff = truth[i] - pred[i];
                    assert(delta[i] == expected_diff);
                    assert(error[i] == expected_diff * expected_diff);
                }
            }

            // Test case 4: Zero values
            {
                const int n = 3;
                float pred[n] = {0.0f, 0.0f, 0.0f};
                float truth[n] = {0.0f, 0.0f, 0.0f};
                float delta[n];
                float error[n];

                l2_kernel(n, pred, truth, delta, error);

                for (int i = 0; i < n; ++i) {
                    assert(delta[i] == 0.0f);
                    assert(error[i] == 0.0f);
                }
            }

            // Test case 5: Single element
            {
                const int n = 1;
                float pred[n] = {5.0f};
                float truth[n] = {7.0f};
                float delta[n];
                float error[n];

                l2_kernel(n, pred, truth, delta, error);

                float expected_diff = truth[0] - pred[0];
                assert(delta[0] == expected_diff);
                assert(error[0] == expected_diff * expected_diff);
            }

            // Test case 6: Large array
            {
                const int n = 1000;
                float pred[n];
                float truth[n];
                float delta[n];
                float error[n];

                for (int i = 0; i < n; ++i) {
                    pred[i] = i * 0.1f;
                    truth[i] = (i + 1) * 0.1f;
                }

                l2_kernel(n, pred, truth, delta, error);

                for (int i = 0; i < n; ++i) {
                    float expected_diff = truth[i] - pred[i];
                    assert(std::abs(delta[i] - expected_diff) < 1e-6f);
                    assert(std::abs(error[i] - (expected_diff * expected_diff)) < 1e-6f);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }