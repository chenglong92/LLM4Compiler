// Optimized code(id = 80): 

void bitPrune(unsigned char* out, float* in, int frontPrune, int outputlength, int inputLength, int n) {
            for (int i = 0; i < n; ++i) {
                int batch = i / outputlength;
                int indexInBatch = i % outputlength;
                int batchInJump = batch * inputLength;
                int indexOutBatch = i % outputlength;
                int batchOutJump = batch * outputlength;
                int frontJump = frontPrune;
                out[batchOutJump + indexOutBatch] = (unsigned char)(in[batchInJump + frontJump + indexInBatch] > 0);
            }
        }