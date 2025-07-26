// original code(id = 170): 
 /*
__global__ void GatherKernel ( const int * input , float * output , int input_size , const float * data , int count , int dim , int data_offset ) { const int thread_index = blockIdx . x * blockDim . x + threadIdx . x ; if ( thread_index < input_size * dim ) { const int input_id = input [ thread_index / dim ] ; const int pos = thread_index % dim ; if ( input_id < count + data_offset && input_id >= data_offset ) { output [ thread_index ] = data [ input_id * dim + pos ] ; } } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void GatherKernel(const int* input, float* output, int input_size, const float* data, int count, int dim, int data_offset);

        void test_GatherKernel() {
            // Test case 1: Basic functionality with valid input
            {
                const int input[] = {1, 2, 3};
                float output[9] = {0};
                const float data[] = {0.0f, 0.1f, 0.2f, 1.0f, 1.1f, 1.2f, 2.0f, 2.1f, 2.2f, 3.0f, 3.1f, 3.2f};
                int input_size = 3;
                int count = 4;
                int dim = 3;
                int data_offset = 0;

                GatherKernel(input, output, input_size, data, count, dim, data_offset);

                assert(output[0] == 1.0f);
                assert(output[1] == 1.1f);
                assert(output[2] == 1.2f);
                assert(output[3] == 2.0f);
                assert(output[4] == 2.1f);
                assert(output[5] == 2.2f);
                assert(output[6] == 3.0f);
                assert(output[7] == 3.1f);
                assert(output[8] == 3.2f);
            }

            // Test case 2: With data offset
            {
                const int input[] = {2, 3, 4};
                float output[9] = {0};
                const float data[] = {0.0f, 0.1f, 0.2f, 1.0f, 1.1f, 1.2f, 2.0f, 2.1f, 2.2f, 3.0f, 3.1f, 3.2f, 4.0f, 4.1f, 4.2f};
                int input_size = 3;
                int count = 3;
                int dim = 3;
                int data_offset = 2;

                GatherKernel(input, output, input_size, data, count, dim, data_offset);

                assert(output[0] == 2.0f);
                assert(output[1] == 2.1f);
                assert(output[2] == 2.2f);
                assert(output[3] == 3.0f);
                assert(output[4] == 3.1f);
                assert(output[5] == 3.2f);
                assert(output[6] == 0.0f); // input_id 4 is out of range (count=3, offset=2)
                assert(output[7] == 0.0f);
                assert(output[8] == 0.0f);
            }

            // Test case 3: Input IDs below data offset
            {
                const int input[] = {0, 1, 2};
                float output[9] = {0};
                const float data[] = {0.0f, 0.1f, 0.2f, 1.0f, 1.1f, 1.2f, 2.0f, 2.1f, 2.2f, 3.0f, 3.1f, 3.2f};
                int input_size = 3;
                int count = 2;
                int dim = 3;
                int data_offset = 2;

                GatherKernel(input, output, input_size, data, count, dim, data_offset);

                assert(output[0] == 0.0f); // input_id 0 is below offset
                assert(output[1] == 0.0f);
                assert(output[2] == 0.0f);
                assert(output[3] == 0.0f); // input_id 1 is below offset
                assert(output[4] == 0.0f);
                assert(output[5] == 0.0f);
                assert(output[6] == 2.0f); // input_id 2 is valid
                assert(output[7] == 2.1f);
                assert(output[8] == 2.2f);
            }

            // Test case 4: Single dimension
            {
                const int input[] = {1, 2, 0};
                float output[3] = {0};
                const float data[] = {10.0f, 20.0f, 30.0f, 40.0f};
                int input_size = 3;
                int count = 4;
                int dim = 1;
                int data_offset = 0;

                GatherKernel(input, output, input_size, data, count, dim, data_offset);

                assert(output[0] == 20.0f);
                assert(output[1] == 30.0f);
                assert(output[2] == 10.0f);
            }

            // Test case 5: Empty input
            {
                const int input[] = {};
                float output[0] = {};
                const float data[] = {1.0f, 2.0f, 3.0f};
                int input_size = 0;
                int count = 3;
                int dim = 1;
                int data_offset = 0;

                GatherKernel(input, output, input_size, data, count, dim, data_offset);
                // No assertions - just checking it doesn't crash
            }
        }

        int main() {
            test_GatherKernel();
            std::cout << "All tests passed!" << std::endl;
            return 0;
        }

        void GatherKernel(const int* input, float* output, int input_size, const float* data, int count, int dim, int data_offset) {
            for (int thread_index = 0; thread_index < input_size * dim; ++thread_index) {
                const int input_id = input[thread_index / dim];
                const int pos = thread_index % dim;
                if (input_id < count + data_offset && input_id >= data_offset) {
                    output[thread_index] = data[input_id * dim + pos];
                }
            }
        }