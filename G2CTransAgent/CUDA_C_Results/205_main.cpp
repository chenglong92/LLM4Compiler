// original code(id = 205): 
 /*
__global__ void inter_kernel ( int NX , float * X , int NY , float * Y , int B , float * OUT ) { int i = ( blockIdx . x + blockIdx . y * gridDim . x ) * blockDim . x + threadIdx . x ; if ( i < ( NX + NY ) * B ) { int b = i / ( NX + NY ) ; int j = i % ( NX + NY ) ; if ( j < NX ) { OUT [ i ] = X [ b * NX + j ] ; } else { OUT [ i ] = Y [ b * NY + j - NX ] ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void inter_kernel(int NX, float* X, int NY, float* Y, int B, float* OUT) {
            for (int i = 0; i < (NX + NY) * B; ++i) {
                int b = i / (NX + NY);
                int j = i % (NX + NY);
                if (j < NX) {
                    OUT[i] = X[b * NX + j];
                } else {
                    OUT[i] = Y[b * NY + j - NX];
                }
            }
        }

        void test_inter_kernel() {
            // Test case 1: Single batch, equal sizes
            {
                int NX = 2, NY = 2, B = 1;
                float X[] = {1.0f, 2.0f};
                float Y[] = {3.0f, 4.0f};
                float OUT[4];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 4; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 2: Single batch, NX > NY
            {
                int NX = 3, NY = 1, B = 1;
                float X[] = {1.0f, 2.0f, 3.0f};
                float Y[] = {4.0f};
                float OUT[4];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 4; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 3: Single batch, NY > NX
            {
                int NX = 1, NY = 3, B = 1;
                float X[] = {1.0f};
                float Y[] = {2.0f, 3.0f, 4.0f};
                float OUT[4];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 4; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 4: Multiple batches, equal sizes
            {
                int NX = 2, NY = 2, B = 2;
                float X[] = {1.0f, 2.0f, 5.0f, 6.0f};
                float Y[] = {3.0f, 4.0f, 7.0f, 8.0f};
                float OUT[8];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 8; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 5: Multiple batches, unequal sizes
            {
                int NX = 2, NY = 1, B = 3;
                float X[] = {1.0f, 2.0f, 4.0f, 5.0f, 7.0f, 8.0f};
                float Y[] = {3.0f, 6.0f, 9.0f};
                float OUT[9];
                float expected[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 9; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 6: Empty X array
            {
                int NX = 0, NY = 2, B = 1;
                float X[] = {};
                float Y[] = {1.0f, 2.0f};
                float OUT[2];
                float expected[] = {1.0f, 2.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 2; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            // Test case 7: Empty Y array
            {
                int NX = 2, NY = 0, B = 1;
                float X[] = {1.0f, 2.0f};
                float Y[] = {};
                float OUT[2];
                float expected[] = {1.0f, 2.0f};
                
                inter_kernel(NX, X, NY, Y, B, OUT);
                
                for (int i = 0; i < 2; ++i) {
                    assert(OUT[i] == expected[i]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_inter_kernel();
            return 0;
        }