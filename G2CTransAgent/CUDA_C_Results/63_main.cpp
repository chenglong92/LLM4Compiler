// original code(id = 63): 
 /*
__global__ void devidecount ( long Xsize , long Ysize , long Zsize , double * pint , int * pcount ) { int n = Xsize * Ysize * 2 + ( Ysize - 2 ) * Zsize * 2 + ( Xsize - 2 ) * ( Zsize - 2 ) * 2 ; long tid = threadIdx . x + blockDim . x * blockIdx . x ; while ( tid < n * n ) { if ( pcount [ tid ] > 1 ) { pint [ tid ] /= pcount [ tid ] ; } tid += blockDim . x * gridDim . x ; } }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void devidecount(long Xsize, long Ysize, long Zsize, double* pint, int* pcount);

        int main() {
            // Test case 1: All pcount elements <= 1 (no division)
            {
                long Xsize = 2, Ysize = 2, Zsize = 2;
                int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
                long total_elements = n * n;
                double* pint = new double[total_elements];
                int* pcount = new int[total_elements];
                
                for (long i = 0; i < total_elements; ++i) {
                    pint[i] = 10.0;
                    pcount[i] = 1;
                }
                
                devidecount(Xsize, Ysize, Zsize, pint, pcount);
                
                for (long i = 0; i < total_elements; ++i) {
                    assert(pint[i] == 10.0);
                }
                
                delete[] pint;
                delete[] pcount;
            }
            
            // Test case 2: Some pcount elements > 1 (division occurs)
            {
                long Xsize = 3, Ysize = 3, Zsize = 3;
                int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
                long total_elements = n * n;
                double* pint = new double[total_elements];
                int* pcount = new int[total_elements];
                
                for (long i = 0; i < total_elements; ++i) {
                    pint[i] = 20.0;
                    pcount[i] = (i % 2 == 0) ? 2 : 1;
                }
                
                devidecount(Xsize, Ysize, Zsize, pint, pcount);
                
                for (long i = 0; i < total_elements; ++i) {
                    if (i % 2 == 0) {
                        assert(pint[i] == 10.0);
                    } else {
                        assert(pint[i] == 20.0);
                    }
                }
                
                delete[] pint;
                delete[] pcount;
            }
            
            // Test case 3: Minimum sizes (1x1x1)
            {
                long Xsize = 1, Ysize = 1, Zsize = 1;
                int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
                long total_elements = n * n;
                double* pint = new double[total_elements];
                int* pcount = new int[total_elements];
                
                for (long i = 0; i < total_elements; ++i) {
                    pint[i] = 5.0;
                    pcount[i] = 5;
                }
                
                devidecount(Xsize, Ysize, Zsize, pint, pcount);
                
                for (long i = 0; i < total_elements; ++i) {
                    assert(pint[i] == 1.0);
                }
                
                delete[] pint;
                delete[] pcount;
            }
            
            // Test case 4: Larger sizes with mixed pcount values
            {
                long Xsize = 4, Ysize = 5, Zsize = 6;
                int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
                long total_elements = n * n;
                double* pint = new double[total_elements];
                int* pcount = new int[total_elements];
                
                for (long i = 0; i < total_elements; ++i) {
                    pint[i] = 100.0;
                    pcount[i] = (i % 10) + 1;  // Values from 1 to 10
                }
                
                devidecount(Xsize, Ysize, Zsize, pint, pcount);
                
                for (long i = 0; i < total_elements; ++i) {
                    int divisor = (i % 10) + 1;
                    if (divisor > 1) {
                        assert(pint[i] == 100.0 / divisor);
                    } else {
                        assert(pint[i] == 100.0);
                    }
                }
                
                delete[] pint;
                delete[] pcount;
            }
            
            std::cout << "All test cases passed!" << std::endl;
            return 0;
        }

        void devidecount(long Xsize, long Ysize, long Zsize, double* pint, int* pcount) {
            int n = Xsize * Ysize * 2 + (Ysize - 2) * Zsize * 2 + (Xsize - 2) * (Zsize - 2) * 2;
            long total_elements = n * n;
            for (long tid = 0; tid < total_elements; ++tid) {
                if (pcount[tid] > 1) {
                    pint[tid] /= pcount[tid];
                }
            }
        }