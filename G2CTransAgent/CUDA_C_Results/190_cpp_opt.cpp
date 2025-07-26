// Optimized code(id = 190): 

void conv1x1(int input_channels, int input_size, int n, float* input_im, float* filter_weight, float* filter_bias, float* output_im) {
            for (int filter_index = 0; filter_index < n; ++filter_index) {
                float* current_filter_weight = filter_weight + filter_index * input_channels;
                float bias = filter_bias[filter_index];
                float* current_output_im = output_im + filter_index * input_size * input_size;
                
                for (int i = 0; i < input_size; ++i) {
                    for (int j = 0; j < input_size; ++j) {
                        float tmp = bias;
                        for (int k = 0; k < input_channels; ++k) {
                            tmp += input_im[k * input_size * input_size + i * input_size + j] * current_filter_weight[k];
                        }
                        current_output_im[i * input_size + j] = (tmp > 0.0f) ? tmp : 0.0f;
                    }
                }
            }
        }