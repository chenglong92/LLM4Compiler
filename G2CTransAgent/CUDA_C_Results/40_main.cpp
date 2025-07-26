// original code(id = 40): 
 /*
__global__ void InitCCL ( int labelList [ ] , int reference [ ] , int width , int height ) { int x = blockIdx . x * blockDim . x + threadIdx . x ; int y = blockIdx . y * blockDim . y + threadIdx . y ; if ( x >= width || y >= height ) return ; int id = x + y * width ; labelList [ id ] = reference [ id ] = id ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void InitCCL(int labelList[], int reference[], int width, int height);

        int main() {
            // Test case 1: Small width and height (3x2)
            {
                const int width = 3;
                const int height = 2;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 2: Width = 1 (1x4)
            {
                const int width = 1;
                const int height = 4;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 3: Height = 1 (5x1)
            {
                const int width = 5;
                const int height = 1;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 4: Width = Height (4x4)
            {
                const int width = 4;
                const int height = 4;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 5: Width > Height (5x3)
            {
                const int width = 5;
                const int height = 3;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 6: Height > Width (2x6)
            {
                const int width = 2;
                const int height = 6;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 7: Minimum dimensions (1x1)
            {
                const int width = 1;
                const int height = 1;
                int labelList[width * height];
                int reference[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
            }

            // Test case 8: Large dimensions (100x100)
            {
                const int width = 100;
                const int height = 100;
                int* labelList = new int[width * height];
                int* reference = new int[width * height];
                
                InitCCL(labelList, reference, width, height);
                
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int id = x + y * width;
                        assert(labelList[id] == id);
                        assert(reference[id] == id);
                    }
                }
                
                delete[] labelList;
                delete[] reference;
            }

            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void InitCCL(int labelList[], int reference[], int width, int height) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int id = x + y * width;
                    labelList[id] = reference[id] = id;
                }
            }
        }