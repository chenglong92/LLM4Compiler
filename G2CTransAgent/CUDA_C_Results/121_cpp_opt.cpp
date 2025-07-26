// Optimized code(id = 121): 

void pad_input(float* f_in, float* f_out, int H, int W, int D, int pad) {
            int new_H = H + 2 * pad;
            int new_W = W + 2 * pad;
            
            for (int dep = 0; dep < D; ++dep) {
                for (int col = 0; col < new_H; ++col) {
                    for (int row = 0; row < new_W; ++row) {
                        int i = dep * new_H * new_W + col * new_W + row;
                        if ((col < pad || col > H + pad - 1) || (row < pad || row > W + pad - 1)) {
                            f_out[i] = 0;
                        } else {
                            int j = dep * H * W + (col - pad) * W + (row - pad);
                            f_out[i] = f_in[j];
                        }
                    }
                }
            }
        }