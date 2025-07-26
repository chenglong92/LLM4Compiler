// original code(id = 56): 
 /*
__global__ void cudaConvertToBits ( int * bit_decisions , unsigned short * bit_stream , int dec_size ) { int dec_index = ( blockIdx . x * blockDim . x ) + threadIdx . x ; int bit_index = dec_index * 2 ; if ( dec_index >= dec_size ) return ; int curr_decision = bit_decisions [ dec_index ] ; bit_stream [ bit_index ] = ( ( curr_decision & 2 ) >> 1 ) ; bit_stream [ bit_index + 1 ] = ( curr_decision & 1 ) ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void cudaConvertToBits(int* bit_decisions, unsigned short* bit_stream, int dec_size) {
            for (int dec_index = 0; dec_index < dec_size; ++dec_index) {
                int bit_index = dec_index * 2;
                int curr_decision = bit_decisions[dec_index];
                bit_stream[bit_index] = ((curr_decision & 2) >> 1);
                bit_stream[bit_index + 1] = (curr_decision & 1);
            }
        }

        void test_cudaConvertToBits() {
            // Test case 1: Basic test with small array
            {
                int decisions[] = {1, 2, 3, 0};
                unsigned short bits[8] = {0};
                int size = 4;
                cudaConvertToBits(decisions, bits, size);
                assert(bits[0] == 0 && bits[1] == 1);  // 1 -> 01
                assert(bits[2] == 1 && bits[3] == 0);  // 2 -> 10
                assert(bits[4] == 1 && bits[5] == 1);  // 3 -> 11
                assert(bits[6] == 0 && bits[7] == 0);  // 0 -> 00
            }

            // Test case 2: Single element array
            {
                int decisions[] = {3};
                unsigned short bits[2] = {0};
                int size = 1;
                cudaConvertToBits(decisions, bits, size);
                assert(bits[0] == 1 && bits[1] == 1);
            }

            // Test case 3: Empty array
            {
                int decisions[] = {1, 2, 3};
                unsigned short bits[6] = {0};
                int size = 0;
                cudaConvertToBits(decisions, bits, size);
                // No assertions - just checking it doesn't crash
            }

            // Test case 4: Negative numbers (using two's complement)
            {
                int decisions[] = {-1, -2};
                unsigned short bits[4] = {0};
                int size = 2;
                cudaConvertToBits(decisions, bits, size);
                // -1 in two's complement is all 1's, so bits 0 and 1 are both 1
                // -2 in two's complement is ...1110, so bits 0 is 0 and bit 1 is 1
                assert(bits[0] == 1 && bits[1] == 1);
                assert(bits[2] == 1 && bits[3] == 0);
            }

            // Test case 5: Large numbers (only least significant 2 bits matter)
            {
                int decisions[] = {1025, 1026};
                unsigned short bits[4] = {0};
                int size = 2;
                cudaConvertToBits(decisions, bits, size);
                // 1025 is 0b10000000001 -> bits 0 and 1 are 01
                // 1026 is 0b10000000010 -> bits 0 and 1 are 10
                assert(bits[0] == 0 && bits[1] == 1);
                assert(bits[2] == 1 && bits[3] == 0);
            }
        }

        int main() {
            test_cudaConvertToBits();
            std::cout << "All tests passed successfully!" << std::endl;
            return 0;
        }