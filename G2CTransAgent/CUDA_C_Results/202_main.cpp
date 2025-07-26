// original code(id = 202): 
 /*
__global__ void logistic_x_ent_kernel ( int n , float * pred , float * truth , float * delta , float * error ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < n ) { float t = truth [ i ] ; float p = pred [ i ] ; error [ i ] = - t * log ( p + .0000001 ) - ( 1 - t ) * log ( 1 - p + .0000001 ) ; delta [ i ] = t - p ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void logistic_x_ent(int n, float* pred, float* truth, float* delta, float* error) {
    for (int i = 0; i < n; ++i) {
        float t = truth[i];
        float p = pred[i];
        error[i] = -t * log(p + 0.0000001f) - (1 - t) * log(1 - p + 0.0000001f);
        delta[i] = t - p;
    }
}

int main() {
    // Test case 1: Basic test with n=3
    {
        int n = 3;
        float pred[] = {0.1f, 0.5f, 0.9f};
        float truth[] = {0.0f, 0.5f, 1.0f};
        float delta[n];
        float error[n];
        
        logistic_x_ent(n, pred, truth, delta, error);
        
        assert(fabs(delta[0] - (0.0f - 0.1f)) < 0.0001f);
        assert(fabs(delta[1] - (0.5f - 0.5f)) < 0.0001f);
        assert(fabs(delta[2] - (1.0f - 0.9f)) < 0.0001f);
        assert(error[0] > 0.0f);
        assert(error[1] > 0.0f);
        assert(error[2] > 0.0f);
    }

    // Test case 2: Edge case with n=1 and truth=1.0
    {
        int n = 1;
        float pred[] = {0.9999999f};
        float truth[] = {1.0f};
        float delta[n];
        float error[n];
        
        logistic_x_ent(n, pred, truth, delta, error);
        
        assert(fabs(delta[0] - (1.0f - 0.9999999f)) < 0.0001f);
        assert(error[0] > 0.0f);
    }

    // Test case 3: Edge case with n=1 and truth=0.0
    {
        int n = 1;
        float pred[] = {0.0000001f};
        float truth[] = {0.0f};
        float delta[n];
        float error[n];
        
        logistic_x_ent(n, pred, truth, delta, error);
        
        assert(fabs(delta[0] - (0.0f - 0.0000001f)) < 0.0001f);
        assert(error[0] > 0.0f);
    }

    // Test case 4: Large n test
    {
        int n = 1000;
        float pred[n];
        float truth[n];
        float delta[n];
        float error[n];
        
        for (int i = 0; i < n; ++i) {
            pred[i] = i % 2 == 0 ? 0.25f : 0.75f;
            truth[i] = i % 2 == 0 ? 0.0f : 1.0f;
        }
        
        logistic_x_ent(n, pred, truth, delta, error);
        
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                assert(fabs(delta[i] - (0.0f - 0.25f)) < 0.0001f);
            } else {
                assert(fabs(delta[i] - (1.0f - 0.75f)) < 0.0001f);
            }
            assert(error[i] > 0.0f);
        }
    }

    // Test case 5: Extreme values
    {
        int n = 2;
        float pred[] = {0.0f, 1.0f};
        float truth[] = {0.0f, 1.0f};
        float delta[n];
        float error[n];
        
        logistic_x_ent(n, pred, truth, delta, error);
        
        assert(fabs(delta[0] - (0.0f - 0.0f)) < 0.0001f);
        assert(fabs(delta[1] - (1.0f - 1.0f)) < 0.0001f);
        assert(error[0] > 0.0f);
        assert(error[1] > 0.0f);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}