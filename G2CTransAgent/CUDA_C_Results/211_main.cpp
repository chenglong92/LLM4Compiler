// original code(id = 211): 
 /*
__global__ void kernelUpdateHead ( int * head , int * d_idxs_out , int n ) { int i = threadIdx . x + blockDim . x * blockIdx . x ; if ( i < n ) { head [ d_idxs_out [ i ] ] = 1 ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void kernelUpdateHead(int* head, int* d_idxs_out, int n) {
            for (int i = 0; i < n; ++i) {
                head[d_idxs_out[i]] = 1;
            }
        }

        void printArray(int* arr, int size) {
            for (int i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        int main() {
            // Test Case 1: Basic Case
            {
                int head[] = {0, 0, 0, 0, 0};
                int d_idxs_out[] = {1, 3};
                int n = 2;
                kernelUpdateHead(head, d_idxs_out, n);
                assert(head[0] == 0);
                assert(head[1] == 1);
                assert(head[2] == 0);
                assert(head[3] == 1);
                assert(head[4] == 0);
                std::cout << "Test Case 1 Passed!" << std::endl;
            }

            // Test Case 2: Empty Case (n = 0)
            {
                int head[] = {0, 0, 0, 0, 0};
                int d_idxs_out[] = {1, 3};
                int n = 0;
                kernelUpdateHead(head, d_idxs_out, n);
                assert(head[0] == 0);
                assert(head[1] == 0);
                assert(head[2] == 0);
                assert(head[3] == 0);
                assert(head[4] == 0);
                std::cout << "Test Case 2 Passed!" << std::endl;
            }

            // Test Case 3: All Indices
            {
                int head[] = {0, 0, 0, 0, 0};
                int d_idxs_out[] = {0, 1, 2, 3, 4};
                int n = 5;
                kernelUpdateHead(head, d_idxs_out, n);
                assert(head[0] == 1);
                assert(head[1] == 1);
                assert(head[2] == 1);
                assert(head[3] == 1);
                assert(head[4] == 1);
                std::cout << "Test Case 3 Passed!" << std::endl;
            }

            // Test Case 4: Repeated Indices
            {
                int head[] = {0, 0, 0, 0, 0};
                int d_idxs_out[] = {1, 1, 1};
                int n = 3;
                kernelUpdateHead(head, d_idxs_out, n);
                assert(head[0] == 0);
                assert(head[1] == 1);
                assert(head[2] == 0);
                assert(head[3] == 0);
                assert(head[4] == 0);
                std::cout << "Test Case 4 Passed!" << std::endl;
            }

            // Test Case 5: Single Index
            {
                int head[] = {0, 0, 0, 0, 0};
                int d_idxs_out[] = {2};
                int n = 1;
                kernelUpdateHead(head, d_idxs_out, n);
                assert(head[0] == 0);
                assert(head[1] == 0);
                assert(head[2] == 1);
                assert(head[3] == 0);
                assert(head[4] == 0);
                std::cout << "Test Case 5 Passed!" << std::endl;
            }

            return 0;
        }