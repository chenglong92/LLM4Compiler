// original code(id = 229): 
 /*
__global__ void conv2 ( float * A , float * kernel , int inputSize , int depth , int kernelSize , int stride , int pad , float * B , int outputSize ) { int i = threadIdx . x + blockDim . x * blockIdx . x ; int j = threadIdx . y + blockDim . y * blockIdx . y ; if ( ! ( i < outputSize ) || ! ( j < outputSize ) ) return ; int Ai = i * stride ; int Aj = j * stride ; int startk = ( pad - Ai ) < 0 ? 0 : pad - Ai ; int endk = kernelSize < ( inputSize + pad - Ai ) ? kernelSize : ( inputSize + pad - Ai ) ; int startl = ( pad - Aj ) < 0 ? 0 : pad - Aj ; int endl = kernelSize < ( inputSize + pad - Aj ) ? kernelSize : ( inputSize + pad - Aj ) ; float sum = 0 ; for ( int d = 0 ; d < depth ; d ++ ) { for ( int k = startk ; k < endk ; k ++ ) { for ( int l = startl ; l < endl ; l ++ ) { sum += A [ d * inputSize * inputSize + ( Ai + k - pad ) * inputSize + Aj + l - pad ] * kernel [ d * kernelSize * kernelSize + k * kernelSize + l ] ; } } B [ d * outputSize * outputSize + i * outputSize + j ] = sum ; } B [ i * outputSize + j ] = sum ; }
*/
// optimized code: 

#include <iostream>
        #include <cmath>
        #include <cstring>

        void conv2(float* A, float* kernel, int inputSize, int depth, int kernelSize, int stride, int pad, float* B, int outputSize) {
            for (int i = 0; i < outputSize; ++i) {
                for (int j = 0; j < outputSize; ++j) {
                    int Ai = i * stride;
                    int Aj = j * stride;
                    int startk = (pad - Ai) < 0 ? 0 : pad - Ai;
                    int endk = kernelSize < (inputSize + pad - Ai) ? kernelSize : (inputSize + pad - Ai);
                    int startl = (pad - Aj) < 0 ? 0 : pad - Aj;
                    int endl = kernelSize < (inputSize + pad - Aj) ? kernelSize : (inputSize + pad - Aj);
                    
                    for (int d = 0; d < depth; ++d) {
                        float sum = 0;
                        for (int k = startk; k < endk; ++k) {
                            for (int l = startl; l < endl; ++l) {
                                sum += A[d * inputSize * inputSize + (Ai + k - pad) * inputSize + Aj + l - pad] * 
                                       kernel[d * kernelSize * kernelSize + k * kernelSize + l];
                            }
                        }
                        B[d * outputSize * outputSize + i * outputSize + j] = sum;
                    }
                }
            }
        }

        bool compareArrays(float* a, float* b, int size, float epsilon = 1e-5) {
            for (int i = 0; i < size; ++i) {
                if (fabs(a[i] - b[i]) > epsilon) {
                    return false;
                }
            }
            return true;
        }

        void printArray(float* arr, int size, const char* name) {
            std::cout << name << ": ";
            for (int i = 0; i < size; ++i) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        int main() {
            // Test case 1: Simple 1x1 convolution with no padding and stride 1
            {
                float A[] = {1, 2, 3, 4};
                float kernel[] = {1};
                float expected[] = {1, 2, 3, 4};
                float B[4];
                
                conv2(A, kernel, 2, 1, 1, 1, 0, B, 2);
                
                if (!compareArrays(B, expected, 4)) {
                    std::cout << "Test case 1 failed!" << std::endl;
                    printArray(B, 4, "Result");
                    printArray(expected, 4, "Expected");
                } else {
                    std::cout << "Test case 1 passed!" << std::endl;
                }
            }

            // Test case 2: 2x2 convolution with padding 1 and stride 1
            {
                float A[] = {1, 2, 3, 4};
                float kernel[] = {1, 0, 0, 1};
                float expected[] = {1, 2, 2, 1, 3, 4, 4, 3, 3, 4, 4, 3, 1, 2, 2, 1};
                float B[16];
                
                conv2(A, kernel, 2, 1, 2, 1, 1, B, 4);
                
                if (!compareArrays(B, expected, 16)) {
                    std::cout << "Test case 2 failed!" << std::endl;
                    printArray(B, 16, "Result");
                    printArray(expected, 16, "Expected");
                } else {
                    std::cout << "Test case 2 passed!" << std::endl;
                }
            }

            // Test case 3: 3x3 convolution with no padding and stride 2
            {
                float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                float kernel[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
                float expected[] = {5, 8, 14, 17};
                float B[4];
                
                conv2(A, kernel, 3, 1, 3, 2, 0, B, 2);
                
                if (!compareArrays(B, expected, 4)) {
                    std::cout << "Test case 3 failed!" << std::endl;
                    printArray(B, 4, "Result");
                    printArray(expected, 4, "Expected");
                } else {
                    std::cout << "Test case 3 passed!" << std::endl;
                }
            }

            // Test case 4: Multi-channel (depth=2) convolution
            {
                float A[] = {1, 2, 3, 4, 5, 6, 7, 8};
                float kernel[] = {1, 0, 0, 1, 0, 1, 1, 0};
                float expected[] = {5, 6, 6, 5, 5, 6, 6, 5};
                float B[8];
                
                conv2(A, kernel, 2, 2, 2, 1, 0, B, 2);
                
                if (!compareArrays(B, expected, 8)) {
                    std::cout << "Test case 4 failed!" << std::endl;
                    printArray(B, 8, "Result");
                    printArray(expected, 8, "Expected");
                } else {
                    std::cout << "Test case 4 passed!" << std::endl;
                }
            }

            // Test case 5: Edge case with large padding
            {
                float A[] = {1, 2, 3, 4};
                float kernel[] = {1, 0, 0, 1};
                float expected[] = {4};
                float B[1];
                
                conv2(A, kernel, 2, 1, 2, 1, 2, B, 1);
                
                if (!compareArrays(B, expected, 1)) {
                    std::cout << "Test case 5 failed!" << std::endl;
                    printArray(B, 1, "Result");
                    printArray(expected, 1, "Expected");
                } else {
                    std::cout << "Test case 5 passed!" << std::endl;
                }
            }

            // Test case 6: Edge case with kernel larger than input
            {
                float A[] = {1, 2, 3, 4};
                float kernel[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
                float expected[] = {4};
                float B[1];
                
                conv2(A, kernel, 2, 1, 4, 1, 0, B, 1);
                
                if (!compareArrays(B, expected, 1)) {
                    std::cout << "Test case 6 failed!" << std::endl;
                    printArray(B, 1, "Result");
                    printArray(expected, 1, "Expected");
                } else {
                    std::cout << "Test case 6 passed!" << std::endl;
                }
            }

            return 0;
        }