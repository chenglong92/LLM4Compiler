// original code(id = 206): 
 /*
__global__ void transferMBR3 ( double * xy_copy , long long * a_copy , int tasks ) { for ( int i = blockIdx . x * blockDim . x + threadIdx . x ; i < tasks ; i += blockDim . x * gridDim . x ) { a_copy [ i ] = xy_copy [ i ] * 10000000 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void transferMBR3(double* xy_copy, long long* a_copy, int tasks) {
            for (int i = 0; i < tasks; ++i) {
                a_copy[i] = xy_copy[i] * 10000000;
            }
        }

        int main() {
            // Test case 1: Basic functionality
            {
                double xy[] = {1.0, 2.0, 3.0};
                long long a[3];
                int tasks = 3;
                transferMBR3(xy, a, tasks);
                assert(a[0] == 10000000LL);
                assert(a[1] == 20000000LL);
                assert(a[2] == 30000000LL);
            }

            // Test case 2: Zero tasks
            {
                double xy[] = {1.0, 2.0, 3.0};
                long long a[3];
                int tasks = 0;
                transferMBR3(xy, a, tasks);
                // No assertions needed as no operations should be performed
            }

            // Test case 3: Negative values
            {
                double xy[] = {-1.5, -2.5, -3.5};
                long long a[3];
                int tasks = 3;
                transferMBR3(xy, a, tasks);
                assert(a[0] == -15000000LL);
                assert(a[1] == -25000000LL);
                assert(a[2] == -35000000LL);
            }

            // Test case 4: Fractional values
            {
                double xy[] = {0.1234567, 1.2345678, 2.3456789};
                long long a[3];
                int tasks = 3;
                transferMBR3(xy, a, tasks);
                assert(a[0] == 1234567LL);
                assert(a[1] == 12345678LL);
                assert(a[2] == 23456789LL);
            }

            // Test case 5: Large values
            {
                double xy[] = {1e18, -1e18, 1e10};
                long long a[3];
                int tasks = 3;
                transferMBR3(xy, a, tasks);
                // Note: These might overflow, but we're testing the behavior
                assert(a[0] == static_cast<long long>(1e18 * 10000000));
                assert(a[1] == static_cast<long long>(-1e18 * 10000000));
                assert(a[2] == static_cast<long long>(1e10 * 10000000));
            }

            // Test case 6: Single element
            {
                double xy[] = {42.0};
                long long a[1];
                int tasks = 1;
                transferMBR3(xy, a, tasks);
                assert(a[0] == 420000000LL);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }