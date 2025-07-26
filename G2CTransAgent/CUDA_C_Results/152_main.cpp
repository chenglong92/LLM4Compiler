// original code(id = 152): 
 /*
__global__ void get_conf_inds ( const float * mlvl_conf , const float conf_thr , int * conf_inds , int dims ) { int tid = blockIdx . x * blockDim . x + threadIdx . x ; if ( tid >= dims ) { return ; } if ( mlvl_conf [ tid ] >= conf_thr ) { conf_inds [ tid ] = 1 ; } else { conf_inds [ tid ] = -1 ; } }
*/
// optimized code: 

#include <iostream>
        #include <vector>
        #include <cassert>

        void get_conf_inds(const float* mlvl_conf, const float conf_thr, int* conf_inds, int dims);

        int main() {
            // Test case 1: All values above threshold
            {
                float confs[] = {0.9f, 0.8f, 0.7f, 0.6f};
                int inds[4];
                get_conf_inds(confs, 0.5f, inds, 4);
                assert(inds[0] == 1 && inds[1] == 1 && inds[2] == 1 && inds[3] == 1);
            }

            // Test case 2: All values below threshold
            {
                float confs[] = {0.4f, 0.3f, 0.2f, 0.1f};
                int inds[4];
                get_conf_inds(confs, 0.5f, inds, 4);
                assert(inds[0] == -1 && inds[1] == -1 && inds[2] == -1 && inds[3] == -1);
            }

            // Test case 3: Mixed values above and below threshold
            {
                float confs[] = {0.6f, 0.4f, 0.7f, 0.3f};
                int inds[4];
                get_conf_inds(confs, 0.5f, inds, 4);
                assert(inds[0] == 1 && inds[1] == -1 && inds[2] == 1 && inds[3] == -1);
            }

            // Test case 4: Empty array
            {
                float confs[] = {};
                int inds[0];
                get_conf_inds(confs, 0.5f, inds, 0);
                // No assertion needed as function should handle dims=0 correctly
            }

            // Test case 5: Single element array
            {
                float confs[] = {0.6f};
                int inds[1];
                get_conf_inds(confs, 0.5f, inds, 1);
                assert(inds[0] == 1);
            }

            // Test case 6: Large array
            {
                const int size = 1000;
                std::vector<float> confs(size, 0.6f);
                std::vector<int> inds(size);
                get_conf_inds(confs.data(), 0.5f, inds.data(), size);
                for (int i = 0; i < size; ++i) {
                    assert(inds[i] == 1);
                }
            }

            // Test case 7: Edge case - exactly at threshold
            {
                float confs[] = {0.5f, 0.5f, 0.5f};
                int inds[3];
                get_conf_inds(confs, 0.5f, inds, 3);
                assert(inds[0] == 1 && inds[1] == 1 && inds[2] == 1);
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void get_conf_inds(const float* mlvl_conf, const float conf_thr, int* conf_inds, int dims) {
            for (int tid = 0; tid < dims; ++tid) {
                if (mlvl_conf[tid] >= conf_thr) {
                    conf_inds[tid] = 1;
                } else {
                    conf_inds[tid] = -1;
                }
            }
        }