// Optimized code(id = 8): 

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