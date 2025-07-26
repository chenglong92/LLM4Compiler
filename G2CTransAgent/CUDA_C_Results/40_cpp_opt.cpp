// Optimized code(id = 40): 

void InitCCL(int labelList[], int reference[], int width, int height) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int id = x + y * width;
                    labelList[id] = reference[id] = id;
                }
            }
        }