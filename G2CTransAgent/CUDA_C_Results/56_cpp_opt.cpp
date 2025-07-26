// Optimized code(id = 56): 

void cudaConvertToBits(int* bit_decisions, unsigned short* bit_stream, int dec_size) {
            for (int dec_index = 0; dec_index < dec_size; ++dec_index) {
                int bit_index = dec_index * 2;
                int curr_decision = bit_decisions[dec_index];
                bit_stream[bit_index] = ((curr_decision & 2) >> 1);
                bit_stream[bit_index + 1] = (curr_decision & 1);
            }
        }