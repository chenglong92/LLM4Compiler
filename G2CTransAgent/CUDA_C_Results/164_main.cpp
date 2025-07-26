// original code(id = 164): 
 /*
__global__ void zero_centroid_vals ( int k , double * __restrict__ Cx_sum , double * __restrict__ Cy_sum , int * __restrict__ Csize ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index < k ) { Cx_sum [ index ] = 0 ; Cy_sum [ index ] = 0 ; Csize [ index ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void zero_centroid_vals(int k, double* Cx_sum, double* Cy_sum, int* Csize);

        int main() {
            // Test case 1: k = 0 (should do nothing)
            {
                double Cx_sum[3] = {1.1, 2.2, 3.3};
                double Cy_sum[3] = {4.4, 5.5, 6.6};
                int Csize[3] = {7, 8, 9};
                
                zero_centroid_vals(0, Cx_sum, Cy_sum, Csize);
                
                assert(Cx_sum[0] == 1.1);
                assert(Cx_sum[1] == 2.2);
                assert(Cx_sum[2] == 3.3);
                assert(Cy_sum[0] == 4.4);
                assert(Cy_sum[1] == 5.5);
                assert(Cy_sum[2] == 6.6);
                assert(Csize[0] == 7);
                assert(Csize[1] == 8);
                assert(Csize[2] == 9);
            }

            // Test case 2: k = 1 (minimum non-zero case)
            {
                double Cx_sum[3] = {1.1, 2.2, 3.3};
                double Cy_sum[3] = {4.4, 5.5, 6.6};
                int Csize[3] = {7, 8, 9};
                
                zero_centroid_vals(1, Cx_sum, Cy_sum, Csize);
                
                assert(Cx_sum[0] == 0.0);
                assert(Cx_sum[1] == 2.2);
                assert(Cx_sum[2] == 3.3);
                assert(Cy_sum[0] == 0.0);
                assert(Cy_sum[1] == 5.5);
                assert(Cy_sum[2] == 6.6);
                assert(Csize[0] == 0);
                assert(Csize[1] == 8);
                assert(Csize[2] == 9);
            }

            // Test case 3: k = 3 (full array size)
            {
                double Cx_sum[3] = {1.1, 2.2, 3.3};
                double Cy_sum[3] = {4.4, 5.5, 6.6};
                int Csize[3] = {7, 8, 9};
                
                zero_centroid_vals(3, Cx_sum, Cy_sum, Csize);
                
                assert(Cx_sum[0] == 0.0);
                assert(Cx_sum[1] == 0.0);
                assert(Cx_sum[2] == 0.0);
                assert(Cy_sum[0] == 0.0);
                assert(Cy_sum[1] == 0.0);
                assert(Cy_sum[2] == 0.0);
                assert(Csize[0] == 0);
                assert(Csize[1] == 0);
                assert(Csize[2] == 0);
            }

            // Test case 4: k = 2 (partial array)
            {
                double Cx_sum[3] = {1.1, 2.2, 3.3};
                double Cy_sum[3] = {4.4, 5.5, 6.6};
                int Csize[3] = {7, 8, 9};
                
                zero_centroid_vals(2, Cx_sum, Cy_sum, Csize);
                
                assert(Cx_sum[0] == 0.0);
                assert(Cx_sum[1] == 0.0);
                assert(Cx_sum[2] == 3.3);
                assert(Cy_sum[0] == 0.0);
                assert(Cy_sum[1] == 0.0);
                assert(Cy_sum[2] == 6.6);
                assert(Csize[0] == 0);
                assert(Csize[1] == 0);
                assert(Csize[2] == 9);
            }

            // Test case 5: large k (but arrays are smaller - undefined behavior but should test)
            // Note: This is dangerous as it accesses out of bounds, but included for completeness
            // Commented out as it's unsafe
            /*
            {
                double Cx_sum[3] = {1.1, 2.2, 3.3};
                double Cy_sum[3] = {4.4, 5.5, 6.6};
                int Csize[3] = {7, 8, 9};
                
                zero_centroid_vals(100, Cx_sum, Cy_sum, Csize);
            }
            */

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void zero_centroid_vals(int k, double* Cx_sum, double* Cy_sum, int* Csize) {
            for (int index = 0; index < k; ++index) {
                Cx_sum[index] = 0;
                Cy_sum[index] = 0;
                Csize[index] = 0;
            }
        }