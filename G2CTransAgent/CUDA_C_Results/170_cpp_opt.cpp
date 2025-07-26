// Optimized code(id = 170): 

void GatherKernel(const int* input, float* output, int input_size, const float* data, int count, int dim, int data_offset) {
            for (int thread_index = 0; thread_index < input_size * dim; ++thread_index) {
                const int input_id = input[thread_index / dim];
                const int pos = thread_index % dim;
                if (input_id < count + data_offset && input_id >= data_offset) {
                    output[thread_index] = data[input_id * dim + pos];
                }
            }
        }