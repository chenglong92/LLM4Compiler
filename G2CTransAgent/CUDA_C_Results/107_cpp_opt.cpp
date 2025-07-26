// Optimized code(id = 107): 

#include <cmath>

void cudaSimpleCorrelator(float* xi, float* xq, float* sr, float* si, int sLength, float* L, int uLength) {
    for (int u = 0; u < uLength; ++u) {
        float real = 0;
        float imag = 0;
        float a, b, c, d;
        
        for (int n = u; n < u + sLength; ++n) {
            a = xi[n];
            b = xq[n];
            c = sr[n - u];
            d = si[n - u] * (-1);
            
            real += (a * c) - (b * d);
            imag += (a * d) + (b * c);
        }
        
        L[u] = sqrt(real * real + imag * imag);
    }
}