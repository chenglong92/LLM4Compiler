// original code(id = 182): 
 /*
__global__ void update_clusters ( int n , int k , double * Cx , double * Cy , double * Cx_sum , double * Cy_sum , int * Csize ) { int index = blockIdx . x * blockDim . x + threadIdx . x ; if ( index < k && Csize [ index ] ) { Cx [ index ] = Cx_sum [ index ] / Csize [ index ] ; Cy [ index ] = Cy_sum [ index ] / Csize [ index ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void update_clusters(int n, int k, double* Cx, double* Cy, double* Cx_sum, double* Cy_sum, int* Csize);

        int main() {
            // Test case 1: Normal case with non-zero Csize
            {
                int n = 10;
                int k = 3;
                double Cx[3] = {0.0, 0.0, 0.0};
                double Cy[3] = {0.0, 0.0, 0.0};
                double Cx_sum[3] = {15.0, 30.0, 45.0};
                double Cy_sum[3] = {30.0, 60.0, 90.0};
                int Csize[3] = {3, 6, 9};

                update_clusters(n, k, Cx, Cy, Cx_sum, Cy_sum, Csize);

                assert(Cx[0] == 5.0);
                assert(Cy[0] == 10.0);
                assert(Cx[1] == 5.0);
                assert(Cy[1] == 10.0);
                assert(Cx[2] == 5.0);
                assert(Cy[2] == 10.0);
            }

            // Test case 2: Some clusters have zero size
            {
                int n = 10;
                int k = 4;
                double Cx[4] = {0.0, 0.0, 0.0, 0.0};
                double Cy[4] = {0.0, 0.0, 0.0, 0.0};
                double Cx_sum[4] = {10.0, 0.0, 20.0, 0.0};
                double Cy_sum[4] = {20.0, 0.0, 40.0, 0.0};
                int Csize[4] = {2, 0, 4, 0};

                update_clusters(n, k, Cx, Cy, Cx_sum, Cy_sum, Csize);

                assert(Cx[0] == 5.0);
                assert(Cy[0] == 10.0);
                assert(Cx[1] == 0.0);  // Should remain unchanged
                assert(Cy[1] == 0.0);  // Should remain unchanged
                assert(Cx[2] == 5.0);
                assert(Cy[2] == 10.0);
                assert(Cx[3] == 0.0);  // Should remain unchanged
                assert(Cy[3] == 0.0);  // Should remain unchanged
            }

            // Test case 3: All clusters have zero size
            {
                int n = 10;
                int k = 3;
                double Cx[3] = {1.0, 2.0, 3.0};
                double Cy[3] = {4.0, 5.0, 6.0};
                double Cx_sum[3] = {10.0, 20.0, 30.0};
                double Cy_sum[3] = {40.0, 50.0, 60.0};
                int Csize[3] = {0, 0, 0};

                update_clusters(n, k, Cx, Cy, Cx_sum, Cy_sum, Csize);

                // All values should remain unchanged
                assert(Cx[0] == 1.0);
                assert(Cy[0] == 4.0);
                assert(Cx[1] == 2.0);
                assert(Cy[1] == 5.0);
                assert(Cx[2] == 3.0);
                assert(Cy[2] == 6.0);
            }

            // Test case 4: k=0 (no clusters)
            {
                int n = 10;
                int k = 0;
                double Cx[1] = {0.0};  // Dummy array
                double Cy[1] = {0.0};  // Dummy array
                double Cx_sum[1] = {0.0};  // Dummy array
                double Cy_sum[1] = {0.0};  // Dummy array
                int Csize[1] = {0};  // Dummy array

                // Should not crash
                update_clusters(n, k, Cx, Cy, Cx_sum, Cy_sum, Csize);
            }

            // Test case 5: Large k
            {
                const int k = 1000;
                double* Cx = new double[k];
                double* Cy = new double[k];
                double* Cx_sum = new double[k];
                double* Cy_sum = new double[k];
                int* Csize = new int[k];

                for (int i = 0; i < k; ++i) {
                    Cx[i] = 0.0;
                    Cy[i] = 0.0;
                    Cx_sum[i] = i * 10.0;
                    Cy_sum[i] = i * 20.0;
                    Csize[i] = i + 1;
                }

                update_clusters(k, k, Cx, Cy, Cx_sum, Cy_sum, Csize);

                for (int i = 0; i < k; ++i) {
                    assert(Cx[i] == (i * 10.0) / (i + 1));
                    assert(Cy[i] == (i * 20.0) / (i + 1));
                }

                delete[] Cx;
                delete[] Cy;
                delete[] Cx_sum;
                delete[] Cy_sum;
                delete[] Csize;
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void update_clusters(int n, int k, double* Cx, double* Cy, double* Cx_sum, double* Cy_sum, int* Csize) {
            for (int index = 0; index < k; ++index) {
                if (Csize[index]) {
                    Cx[index] = Cx_sum[index] / Csize[index];
                    Cy[index] = Cy_sum[index] / Csize[index];
                }
            }
        }