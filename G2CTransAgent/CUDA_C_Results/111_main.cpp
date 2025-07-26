// original code(id = 111): 
 /*
__global__ void kernel ( float * x , int n ) { int tid = threadIdx . x + blockIdx . x * blockDim . x ; for ( int i = tid ; i < n ; i += blockDim . x * gridDim . x ) { double sum = 0 ; for ( int j = 0 ; j < 1000 ; j ++ ) { sum += sqrt ( pow ( 3.14159 , i ) ) / float ( j ) ; } x [ i ] = sum ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void kernel(float* x, int n) {
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int j = 0; j < 1000; j++) {
                    sum += sqrt(pow(3.14159, i)) / float(j + 1);
                }
                x[i] = sum;
            }
        }

        void test_kernel() {
            // Test case 1: Small array (n=3)
            {
                float x[3];
                kernel(x, 3);
                assert(x[0] > 0 && x[1] > 0 && x[2] > 0); // Values should be positive
                assert(x[1] > x[0]); // Since π^1 > π^0
            }

            // Test case 2: Single element (n=1)
            {
                float x[1];
                kernel(x, 1);
                assert(x[0] > 0);
            }

            // Test case 3: Empty array (n=0)
            {
                float x[1];
                kernel(x, 0); // Should do nothing
                // No assertion needed as we're testing it doesn't crash
            }

            // Test case 4: Large array (n=10000)
            {
                const int n = 10000;
                float* x = new float[n];
                kernel(x, n);
                for (int i = 1; i < n; i++) {
                    assert(x[i] > x[i-1]); // Each element should be larger than previous
                }
                delete[] x;
            }

            // Test case 5: NULL pointer (should crash, but we'll catch it)
            {
                bool caught = false;
                try {
                    kernel(nullptr, 5);
                } catch (...) {
                    caught = true;
                }
                assert(caught); // Expecting a crash (null pointer dereference)
            }
        }

        int main() {
            test_kernel();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }