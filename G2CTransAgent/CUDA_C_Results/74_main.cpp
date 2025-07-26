// original code(id = 74): 
 /*
__global__ void cudaBYUSimplified ( float * xi , float * xq , float * sr , float * si , int N , int Lq , float * L ) { int u = ( blockIdx . x * blockDim . x ) + threadIdx . x ; if ( u >= N ) return ; float uSum = 0 ; float r_i , r_q , q_i , q_q ; float realPart , imagPart ; for ( int k = 0 ; k <= 7 ; k ++ ) { realPart = 0 ; imagPart = 0 ; for ( int l = 0 ; l < Lq ; l ++ ) { r_i = xi [ u + k * Lq + l ] ; r_q = xq [ u + k * Lq + l ] ; q_i = sr [ l ] ; q_q = si [ l ] * ( -1 ) ; realPart += ( r_i * q_i ) - ( r_q * q_q ) ; imagPart += ( r_i * q_q ) + ( r_q * q_i ) ; } uSum += ( realPart * realPart ) + ( imagPart * imagPart ) ; } L [ u ] = uSum ; }
*/
// optimized code: 

#include <iostream>
        #include <cstdlib>
        #include <cmath>
        #include <vector>
        #include <cassert>

        void cudaBYUSimplified(float* xi, float* xq, float* sr, float* si, int N, int Lq, float* L);

        int main() {
            // Test Case 1: Normal case with small values
            {
                const int N = 5;
                const int Lq = 3;
                float xi[N * 8 * Lq] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 
                                        11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f, 19.0f, 20.0f,
                                        21.0f, 22.0f, 23.0f, 24.0f, 25.0f, 26.0f, 27.0f, 28.0f, 29.0f, 30.0f,
                                        31.0f, 32.0f, 33.0f, 34.0f, 35.0f, 36.0f, 37.0f, 38.0f, 39.0f, 40.0f,
                                        41.0f, 42.0f, 43.0f, 44.0f, 45.0f, 46.0f, 47.0f, 48.0f, 49.0f, 50.0f,
                                        51.0f, 52.0f, 53.0f, 54.0f, 55.0f, 56.0f, 57.0f, 58.0f, 59.0f, 60.0f,
                                        61.0f, 62.0f, 63.0f, 64.0f, 65.0f, 66.0f, 67.0f, 68.0f, 69.0f, 70.0f,
                                        71.0f, 72.0f, 73.0f, 74.0f, 75.0f, 76.0f, 77.0f, 78.0f, 79.0f, 80.0f,
                                        81.0f, 82.0f, 83.0f, 84.0f, 85.0f, 86.0f, 87.0f, 88.0f, 89.0f, 90.0f,
                                        91.0f, 92.0f, 93.0f, 94.0f, 95.0f, 96.0f, 97.0f, 98.0f, 99.0f, 100.0f,
                                        101.0f, 102.0f, 103.0f, 104.0f, 105.0f, 106.0f, 107.0f, 108.0f, 109.0f, 110.0f,
                                        111.0f, 112.0f, 113.0f, 114.0f, 115.0f, 116.0f, 117.0f, 118.0f, 119.0f, 120.0f};
                float xq[N * 8 * Lq] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 
                                        1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f,
                                        2.1f, 2.2f, 2.3f, 2.4f, 2.5f, 2.6f, 2.7f, 2.8f, 2.9f, 3.0f,
                                        3.1f, 3.2f, 3.3f, 3.4f, 3.5f, 3.6f, 3.7f, 3.8f, 3.9f, 4.0f,
                                        4.1f, 4.2f, 4.3f, 4.4f, 4.5f, 4.6f, 4.7f, 4.8f, 4.9f, 5.0f,
                                        5.1f, 5.2f, 5.3f, 5.4f, 5.5f, 5.6f, 5.7f, 5.8f, 5.9f, 6.0f,
                                        6.1f, 6.2f, 6.3f, 6.4f, 6.5f, 6.6f, 6.7f, 6.8f, 6.9f, 7.0f,
                                        7.1f, 7.2f, 7.3f, 7.4f, 7.5f, 7.6f, 7.7f, 7.8f, 7.9f, 8.0f,
                                        8.1f, 8.2f, 8.3f, 8.4f, 8.5f, 8.6f, 8.7f, 8.8f, 8.9f, 9.0f,
                                        9.1f, 9.2f, 9.3f, 9.4f, 9.5f, 9.6f, 9.7f, 9.8f, 9.9f, 10.0f,
                                        10.1f, 10.2f, 10.3f, 10.4f, 10.5f, 10.6f, 10.7f, 10.8f, 10.9f, 11.0f,
                                        11.1f, 11.2f, 11.3f, 11.4f, 11.5f, 11.6f, 11.7f, 11.8f, 11.9f, 12.0f};
                float sr[Lq] = {0.5f, 0.6f, 0.7f};
                float si[Lq] = {0.8f, 0.9f, 1.0f};
                float L[N] = {0.0f};
                
                cudaBYUSimplified(xi, xq, sr, si, N, Lq, L);
                
                for (int i = 0; i < N; ++i) {
                    assert(L[i] > 0.0f);
                }
                std::cout << "Test Case 1 passed." << std::endl;
            }
            
            // Test Case 2: Boundary case with N = 1 and Lq = 1
            {
                const int N = 1;
                const int Lq = 1;
                float xi[N * 8 * Lq] = {1.0f};
                float xq[N * 8 * Lq] = {0.1f};
                float sr[Lq] = {0.5f};
                float si[Lq] = {0.8f};
                float L[N] = {0.0f};
                
                cudaBYUSimplified(xi, xq, sr, si, N, Lq, L);
                
                assert(L[0] > 0.0f);
                std::cout << "Test Case 2 passed." << std::endl;
            }
            
            // Test Case 3: Error case with N = 0 (should not crash)
            {
                const int N = 0;
                const int Lq = 3;
                float* xi = nullptr;
                float* xq = nullptr;
                float sr[Lq] = {0.5f, 0.6f, 0.7f};
                float si[Lq] = {0.8f, 0.9f, 1.0f};
                float* L = nullptr;
                
                cudaBYUSimplified(xi, xq, sr, si, N, Lq, L);
                std::cout << "Test Case 3 passed (no crash with N=0)." << std::endl;
            }
            
            // Test Case 4: Large values case
            {
                const int N = 2;
                const int Lq = 2;
                float xi[N * 8 * Lq] = {1000.0f, 2000.0f, 3000.0f, 4000.0f, 5000.0f, 6000.0f, 7000.0f, 8000.0f,
                                        9000.0f, 10000.0f, 11000.0f, 12000.0f, 13000.0f, 14000.0f, 15000.0f, 16000.0f};
                float xq[N * 8 * Lq] = {100.0f, 200.0f, 300.0f, 400.0f, 500.0f, 600.0f, 700.0f, 800.0f,
                                        900.0f, 1000.0f, 1100.0f, 1200.0f, 1300.0f, 1400.0f, 1500.0f, 1600.0f};
                float sr[Lq] = {50.0f, 60.0f};
                float si[Lq] = {80.0f, 90.0f};
                float L[N] = {0.0f};
                
                cudaBYUSimplified(xi, xq, sr, si, N, Lq, L);
                
                for (int i = 0; i < N; ++i) {
                    assert(L[i] > 0.0f);
                }
                std::cout << "Test Case 4 passed." << std::endl;
            }
            
            // Test Case 5: Mixed positive and negative values
            {
                const int N = 3;
                const int Lq = 2;
                float xi[N * 8 * Lq] = {-1.0f, 2.0f, -3.0f, 4.0f, -5.0f, 6.0f, -7.0f, 8.0f,
                                        -9.0f, 10.0f, -11.0f, 12.0f, -13.0f, 14.0f, -15.0f, 16.0f,
                                        -17.0f, 18.0f, -19.0f, 20.0f, -21.0f, 22.0f, -23.0f, 24.0f};
                float xq[N * 8 * Lq] = {0.1f, -0.2f, 0.3f, -0.4f, 0.5f, -0.6f, 0.7f, -0.8f,
                                        0.9f, -1.0f, 1.1f, -1.2f, 1.3f, -1.4f, 1.5f, -1.6f,
                                        1.7f, -1.8f, 1.9f, -2.0f, 2.1f, -2.2f, 2.3f, -2.4f};
                float sr[Lq] = {-0.5f, 0.6f};
                float si[Lq] = {0.8f, -0.9f};
                float L[N] = {0.0f};
                
                cudaBYUSimplified(xi, xq, sr, si, N, Lq, L);
                
                for (int i = 0; i < N; ++i) {
                    assert(L[i] > 0.0f);
                }
                std::cout << "Test Case 5 passed." << std::endl;
            }
            
            return 0;
        }