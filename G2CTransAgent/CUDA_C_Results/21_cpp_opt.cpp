// Optimized code(id = 21): 

#include <cstdint>

void bit8Channels(unsigned char* out, unsigned char* in, int channel, int n) {
    for (int i = 0; i < n; ++i) {
        int firstIndexToGrab = i * 8;
        unsigned char bit0 = (in[firstIndexToGrab + 0] & 0x01) << 0;
        unsigned char bit1 = (in[firstIndexToGrab + 1] & 0x01) << 1;
        unsigned char bit2 = (in[firstIndexToGrab + 2] & 0x01) << 2;
        unsigned char bit3 = (in[firstIndexToGrab + 3] & 0x01) << 3;
        unsigned char bit4 = (in[firstIndexToGrab + 4] & 0x01) << 4;
        unsigned char bit5 = (in[firstIndexToGrab + 5] & 0x01) << 5;
        unsigned char bit6 = (in[firstIndexToGrab + 6] & 0x01) << 6;
        unsigned char bit7 = (in[firstIndexToGrab + 7] & 0x01) << 7;
        unsigned char output = bit7 | bit6 | bit5 | bit4 | bit3 | bit2 | bit1 | bit0;
        int outputIndex = i * 8 + channel - 1;
        out[outputIndex] = output;
    }
}