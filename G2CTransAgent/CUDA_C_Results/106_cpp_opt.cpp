// Optimized code(id = 106): 

void nlf_down_forward(const int n, const float* filters, const int channel, const int height, const int width, const int wsize, float* top_data) {
            for (int index = 0; index < n; ++index) {
                int step = height * width;
                int base = index * step;
                int fbase = index / channel * wsize * step;
                
                for (int row = 0; row < height; ++row) {
                    for (int col = 0; col < width; ++col) {
                        float temp = 0;
                        int r = row;
                        int c = col;
                        int shift = 0 * step + row * width + col;
                        temp += top_data[base + r * width + c] * filters[fbase + shift];
                        
                        r = row - 1;
                        c = col;
                        shift = 1 * step + row * width + col;
                        if (r >= 0)
                            temp += top_data[base + r * width + c] * filters[fbase + shift];
                        else
                            temp += top_data[base + row * width + col] * filters[fbase + shift];
                        
                        r = row - 1;
                        c = col - 1;
                        shift = 2 * step + row * width + col;
                        if (r >= 0 && c >= 0)
                            temp += top_data[base + r * width + c] * filters[fbase + shift];
                        else
                            temp += top_data[base + row * width + col] * filters[fbase + shift];
                        
                        r = row - 1;
                        c = col + 1;
                        shift = 3 * step + row * width + col;
                        if (r >= 0 && c < width)
                            temp += top_data[base + r * width + c] * filters[fbase + shift];
                        else
                            temp += top_data[base + row * width + col] * filters[fbase + shift];
                        
                        r = row;
                        c = col - 1;
                        shift = 4 * step + row * width + col;
                        if (c >= 0)
                            temp += top_data[base + r * width + c] * filters[fbase + shift];
                        else
                            temp += top_data[base + row * width + col] * filters[fbase + shift];
                        
                        top_data[base + row * width + col] = temp;
                    }
                }
            }
        }