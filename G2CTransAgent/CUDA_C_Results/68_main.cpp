// original code(id = 68): 
 /*
__global__ void grayscale ( unsigned char * input , unsigned char * output , int size ) { unsigned char r , g , b ; int i = threadIdx . x + blockDim . x * blockIdx . x ; if ( i < size ) { r = input [ 3 * i ] ; g = input [ 3 * i + 1 ] ; b = input [ 3 * i + 2 ] ; output [ i ] = ( unsigned char ) ( 0.21 * ( float ) r + 0.71 * ( float ) g + 0.07 * ( float ) b ) ; } }
*/
// optimized code: 

#include <cassert>
        #include <cstring>

        void grayscale(unsigned char* input, unsigned char* output, int size);

        int main() {
            // Test case 1: Simple RGB to grayscale conversion
            unsigned char input1[] = {255, 255, 255, 0, 0, 0, 128, 128, 128};
            unsigned char output1[3];
            grayscale(input1, output1, 3);
            assert(output1[0] == 255); // White should convert to 255
            assert(output1[1] == 0);   // Black should convert to 0
            assert(output1[2] == 128); // Mid-gray should stay 128

            // Test case 2: Single pixel conversion
            unsigned char input2[] = {100, 150, 200};
            unsigned char output2[1];
            grayscale(input2, output2, 1);
            assert(output2[0] == static_cast<unsigned char>(0.21f * 100 + 0.71f * 150 + 0.07f * 200));

            // Test case 3: Empty input (size 0)
            unsigned char input3[] = {0, 0, 0};
            unsigned char output3[0];
            grayscale(input3, output3, 0);
            // No assertion needed as function should handle size 0 without errors

            // Test case 4: Large array
            const int largeSize = 1000;
            unsigned char input4[3 * largeSize];
            unsigned char output4[largeSize];
            for (int i = 0; i < largeSize; ++i) {
                input4[3 * i] = i % 256;
                input4[3 * i + 1] = (i + 50) % 256;
                input4[3 * i + 2] = (i + 100) % 256;
            }
            grayscale(input4, output4, largeSize);
            for (int i = 0; i < largeSize; ++i) {
                unsigned char expected = static_cast<unsigned char>(
                    0.21f * input4[3 * i] + 0.71f * input4[3 * i + 1] + 0.07f * input4[3 * i + 2]);
                assert(output4[i] == expected);
            }

            // Test case 5: Check boundary values
            unsigned char input5[] = {0, 0, 0, 255, 255, 255, 1, 1, 1, 254, 254, 254};
            unsigned char output5[4];
            grayscale(input5, output5, 4);
            assert(output5[0] == 0);
            assert(output5[1] == 255);
            assert(output5[2] == 1);
            assert(output5[3] == 254);

            return 0;
        }