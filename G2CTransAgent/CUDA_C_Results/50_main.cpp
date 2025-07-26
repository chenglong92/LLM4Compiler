// original code(id = 50): 
 /*
__global__ void cuda_set_sg ( int * sxz , int sxbeg , int szbeg , int jsx , int jsz , int ns , int npml , int nnz ) { int id = threadIdx . x + blockDim . x * blockIdx . x ; if ( id < ns ) sxz [ id ] = nnz * ( sxbeg + id * jsx + npml ) + ( szbeg + id * jsz + npml ) ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void cuda_set_sg(int* sxz, int sxbeg, int szbeg, int jsx, int jsz, int ns, int npml, int nnz) {
    for (int id = 0; id < ns; ++id) {
        sxz[id] = nnz * (sxbeg + id * jsx + npml) + (szbeg + id * jsz + npml);
    }
}

void test_normal_case() {
    const int ns = 5;
    int sxz[ns];
    int sxbeg = 1, szbeg = 2, jsx = 3, jsz = 4, npml = 1, nnz = 10;
    
    cuda_set_sg(sxz, sxbeg, szbeg, jsx, jsz, ns, npml, nnz);
    
    int expected[ns] = {32, 72, 112, 152, 192};
    for (int i = 0; i < ns; ++i) {
        assert(sxz[i] == expected[i]);
    }
}

void test_edge_case_zero_ns() {
    const int ns = 0;
    int sxz[1]; // Dummy array since ns is 0
    int sxbeg = 1, szbeg = 2, jsx = 3, jsz = 4, npml = 1, nnz = 10;
    
    cuda_set_sg(sxz, sxbeg, szbeg, jsx, jsz, ns, npml, nnz);
    // No assertion needed as function shouldn't modify anything when ns=0
}

void test_edge_case_negative_values() {
    const int ns = 3;
    int sxz[ns];
    int sxbeg = -1, szbeg = -2, jsx = -3, jsz = -4, npml = -1, nnz = 10;
    
    cuda_set_sg(sxz, sxbeg, szbeg, jsx, jsz, ns, npml, nnz);
    
    int expected[ns] = {-32, -92, -152};
    for (int i = 0; i < ns; ++i) {
        assert(sxz[i] == expected[i]);
    }
}

void test_large_values() {
    const int ns = 2;
    int sxz[ns];
    int sxbeg = 10000, szbeg = 20000, jsx = 30000, jsz = 40000, npml = 1000, nnz = 100000;
    
    cuda_set_sg(sxz, sxbeg, szbeg, jsx, jsz, ns, npml, nnz);
    
    int expected[ns] = {1101000000, 1412000000};
    for (int i = 0; i < ns; ++i) {
        assert(sxz[i] == expected[i]);
    }
}

int main() {
    test_normal_case();
    test_edge_case_zero_ns();
    test_edge_case_negative_values();
    test_large_values();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}