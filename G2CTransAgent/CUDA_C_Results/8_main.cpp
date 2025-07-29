// original code(id = 8): 
 /*
__global__ void convertKinectDisparityToRegularDisparity_kernel ( float * d_regularDisparity , int d_regularDisparityPitch , const float * d_KinectDisparity , int d_KinectDisparityPitch , int width , int height ) { const int x = blockIdx . x * blockDim . x + threadIdx . x ; const int y = blockIdx . y * blockDim . y + threadIdx . y ; if ( ( x < width ) & ( y < height ) ) { float d_in = * ( ( float * ) ( ( char * ) d_KinectDisparity + y * d_KinectDisparityPitch ) + x ) ; float d_out = ( d_in == 0.0f ) ? 1 : - d_in ; * ( ( float * ) ( ( char * ) d_regularDisparity + y * d_regularDisparityPitch ) + x ) = d_out ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <cstring>

        void convertKinectDisparityToRegularDisparity(float* d_regularDisparity, int d_regularDisparityPitch,
                                             const float* d_KinectDisparity, int d_KinectDisparityPitch,
                                             int width, int height);

        int main() {
            // Test case 1: Small 2x2 array with zero and non-zero values
            {
                const int width = 2;
                const int height = 2;
                const int pitch = width * sizeof(float);
                
                float kinectDisparity[width * height] = {0.0f, 1.0f, 2.0f, 0.0f};
                float regularDisparity[width * height] = {0};
                
                convertKinectDisparityToRegularDisparity(regularDisparity, pitch,
                                                        kinectDisparity, pitch,
                                                        width, height);
                
                assert(regularDisparity[0] == 1.0f);
                assert(regularDisparity[1] == -1.0f);
                assert(regularDisparity[2] == -2.0f);
                assert(regularDisparity[3] == 1.0f);
            }

            // Test case 2: Larger array with different pitch (extra padding)
            {
                const int width = 3;
                const int height = 2;
                const int extraPadding = 1;
                const int kinectPitch = (width + extraPadding) * sizeof(float);
                const int regularPitch = (width + extraPadding) * sizeof(float);
                
                float* kinectDisparity = new float[(width + extraPadding) * height];
                float* regularDisparity = new float[(width + extraPadding) * height];
                
                // Initialize with test data
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        kinectDisparity[y * (width + extraPadding) + x] = (x + y) * 0.5f;
                    }
                    // Set one zero value per row
                    kinectDisparity[y * (width + extraPadding) + 1] = 0.0f;
                }
                
                convertKinectDisparityToRegularDisparity(regularDisparity, regularPitch,
                                                        kinectDisparity, kinectPitch,
                                                        width, height);
                
                // Verify results
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        float expected;
                        if (x == 1) {
                            expected = 1.0f;
                        } else {
                            expected = -((x + y) * 0.5f);
                        }
                        assert(regularDisparity[y * (width + extraPadding) + x] == expected);
                    }
                }
                
                delete[] kinectDisparity;
                delete[] regularDisparity;
            }

            // Test case 3: All zeros
            {
                const int width = 4;
                const int height = 1;
                const int pitch = width * sizeof(float);
                
                float kinectDisparity[width * height] = {0};
                float regularDisparity[width * height] = {0};
                
                convertKinectDisparityToRegularDisparity(regularDisparity, pitch,
                                                        kinectDisparity, pitch,
                                                        width, height);
                
                for (int i = 0; i < width * height; ++i) {
                    assert(regularDisparity[i] == 1.0f);
                }
            }

            // Test case 4: All non-zeros
            {
                const int width = 1;
                const int height = 3;
                const int pitch = width * sizeof(float);
                
                float kinectDisparity[width * height] = {0.5f, 1.0f, 1.5f};
                float regularDisparity[width * height] = {0};
                
                convertKinectDisparityToRegularDisparity(regularDisparity, pitch,
                                                        kinectDisparity, pitch,
                                                        width, height);
                
                assert(regularDisparity[0] == -0.5f);
                assert(regularDisparity[1] == -1.0f);
                assert(regularDisparity[2] == -1.5f);
            }

            std::cout << "All tests passed!" << std::endl;
            return 0;
        }

        void convertKinectDisparityToRegularDisparity(float* d_regularDisparity, int d_regularDisparityPitch,
                                             const float* d_KinectDisparity, int d_KinectDisparityPitch,
                                             int width, int height) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    float d_in = *((float*)((char*)d_KinectDisparity + y * d_KinectDisparityPitch) + x);
                    float d_out = (d_in == 0.0f) ? 1 : -d_in;
                    *((float*)((char*)d_regularDisparity + y * d_regularDisparityPitch) + x) = d_out;
                }
            }
        }