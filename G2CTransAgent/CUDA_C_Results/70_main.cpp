// original code(id = 70): 
 /*
__global__ void subsample_ind_and_labels_GPU ( int * d_ind_sub , const int * d_ind , unsigned int * d_label_sub , const unsigned int * d_label , int n_out , float inv_sub_factor ) { unsigned int ind_out = blockIdx . x * blockDim . x + threadIdx . x ; if ( ind_out < n_out ) { int ind_in = ( int ) floorf ( ( float ) ( ind_out ) * inv_sub_factor ) ; d_ind_sub [ ind_out ] = d_ind [ ind_in ] ; d_label_sub [ ind_out ] = d_label [ ind_in ] ; } }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cassert>

        void subsample_ind_and_labels_CPU(int* d_ind_sub, const int* d_ind, unsigned int* d_label_sub, const unsigned int* d_label, int n_out, float inv_sub_factor) {
            for (unsigned int ind_out = 0; ind_out < n_out; ++ind_out) {
                int ind_in = static_cast<int>(floorf(static_cast<float>(ind_out) * inv_sub_factor));
                d_ind_sub[ind_out] = d_ind[ind_in];
                d_label_sub[ind_out] = d_label[ind_in];
            }
        }

        int main() {
            // Test case 1: Basic test with n_out = 5 and inv_sub_factor = 1.0
            {
                const int n_out = 5;
                const float inv_sub_factor = 1.0f;
                int d_ind[n_out] = {10, 20, 30, 40, 50};
                unsigned int d_label[n_out] = {1, 2, 3, 4, 5};
                int d_ind_sub[n_out] = {0};
                unsigned int d_label_sub[n_out] = {0};

                subsample_ind_and_labels_CPU(d_ind_sub, d_ind, d_label_sub, d_label, n_out, inv_sub_factor);

                for (int i = 0; i < n_out; ++i) {
                    assert(d_ind_sub[i] == d_ind[i]);
                    assert(d_label_sub[i] == d_label[i]);
                }
            }

            // Test case 2: Test with n_out = 3 and inv_sub_factor = 2.0
            {
                const int n_out = 3;
                const float inv_sub_factor = 2.0f;
                int d_ind[6] = {10, 20, 30, 40, 50, 60};
                unsigned int d_label[6] = {1, 2, 3, 4, 5, 6};
                int d_ind_sub[n_out] = {0};
                unsigned int d_label_sub[n_out] = {0};

                subsample_ind_and_labels_CPU(d_ind_sub, d_ind, d_label_sub, d_label, n_out, inv_sub_factor);

                assert(d_ind_sub[0] == d_ind[0]);
                assert(d_label_sub[0] == d_label[0]);
                assert(d_ind_sub[1] == d_ind[2]);
                assert(d_label_sub[1] == d_label[2]);
                assert(d_ind_sub[2] == d_ind[4]);
                assert(d_label_sub[2] == d_label[4]);
            }

            // Test case 3: Test with n_out = 0 (empty output)
            {
                const int n_out = 0;
                const float inv_sub_factor = 1.0f;
                int d_ind[1] = {10};
                unsigned int d_label[1] = {1};
                int d_ind_sub[1] = {0};
                unsigned int d_label_sub[1] = {0};

                subsample_ind_and_labels_CPU(d_ind_sub, d_ind, d_label_sub, d_label, n_out, inv_sub_factor);
                // No assertions needed as function shouldn't process anything
            }

            // Test case 4: Test with fractional inv_sub_factor
            {
                const int n_out = 4;
                const float inv_sub_factor = 1.5f;
                int d_ind[6] = {10, 20, 30, 40, 50, 60};
                unsigned int d_label[6] = {1, 2, 3, 4, 5, 6};
                int d_ind_sub[n_out] = {0};
                unsigned int d_label_sub[n_out] = {0};

                subsample_ind_and_labels_CPU(d_ind_sub, d_ind, d_label_sub, d_label, n_out, inv_sub_factor);

                assert(d_ind_sub[0] == d_ind[0]);
                assert(d_label_sub[0] == d_label[0]);
                assert(d_ind_sub[1] == d_ind[1]);
                assert(d_label_sub[1] == d_label[1]);
                assert(d_ind_sub[2] == d_ind[3]);
                assert(d_label_sub[2] == d_label[3]);
                assert(d_ind_sub[3] == d_ind[4]);
                assert(d_label_sub[3] == d_label[4]);
            }

            // Test case 5: Test with large n_out
            {
                const int n_out = 1000;
                const float inv_sub_factor = 0.1f;
                int d_ind[100] = {0};
                unsigned int d_label[100] = {0};
                for (int i = 0; i < 100; ++i) {
                    d_ind[i] = i * 10;
                    d_label[i] = i;
                }
                int d_ind_sub[n_out] = {0};
                unsigned int d_label_sub[n_out] = {0};

                subsample_ind_and_labels_CPU(d_ind_sub, d_ind, d_label_sub, d_label, n_out, inv_sub_factor);

                for (int i = 0; i < n_out; ++i) {
                    int expected_index = static_cast<int>(floorf(static_cast<float>(i) * inv_sub_factor));
                    assert(d_ind_sub[i] == d_ind[expected_index]);
                    assert(d_label_sub[i] == d_label[expected_index]);
                }
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }