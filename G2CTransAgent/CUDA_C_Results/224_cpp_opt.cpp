// Optimized code(id = 224): 

#include <cmath>

void cudaChoiLee(float* xi, float* xq, float* sr, float* si, int N, float* L) {
    for (int u = 0; u < N; ++u) {
        float uSum = 0;
        for (int i = 0; i < N; ++i) {
            float ksum_i = 0;
            float ksum_q = 0;
            for (int k = 0; k < N - i; ++k) {
                float r_i = xi[u + k + i];
                float r_q = xq[u + k + i];
                float rconj_i = xi[u + k];
                float rconj_q = xq[u + k] * (-1);
                
                float s_i = sr[k];
                float s_q = si[k];
                float sconj_i = sr[k + i];
                float sconj_q = si[k + i] * (-1);
                
                float rsum_i = (r_i * rconj_i) - (r_q * rconj_q);
                float rsum_q = (r_i * rconj_q) + (r_q * rconj_i);
                
                float ssum_i = (s_i * sconj_i) - (s_q * sconj_q);
                float ssum_q = (s_i * sconj_q) + (s_q * sconj_i);
                
                ksum_i += (rsum_i * ssum_i) - (rsum_q * ssum_q);
                ksum_q += (rsum_i * ssum_q) + (rsum_q * ssum_i);
            }
            uSum += sqrt((ksum_i * ksum_i) + (ksum_q * ksum_q));
        }
        L[u] = uSum;
    }
}