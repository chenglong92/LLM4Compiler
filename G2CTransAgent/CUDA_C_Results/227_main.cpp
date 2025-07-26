// original code(id = 227): 
 /*
__global__ void create_p_vect ( float * node_info1 , float * node_info2 , float * p , int n_nodes_1 , int n_nodes_2 ) { int tx = threadIdx . x + blockDim . x * blockIdx . x ; int ty = threadIdx . y + blockDim . y * blockIdx . y ; float cutoff = 0.5 ; if ( ( tx < n_nodes_1 ) && ( ty < n_nodes_2 ) ) { int ind = tx * n_nodes_2 + ty ; if ( ( node_info1 [ tx ] < cutoff ) && ( node_info2 [ ty ] < cutoff ) ) p [ ind ] = 0 ; else p [ ind ] = node_info1 [ tx ] * node_info2 [ ty ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void create_p_vect(float* node_info1, float* node_info2, float* p, int n_nodes_1, int n_nodes_2) {
    float cutoff = 0.5f;
    
    for (int tx = 0; tx < n_nodes_1; ++tx) {
        for (int ty = 0; ty < n_nodes_2; ++ty) {
            int ind = tx * n_nodes_2 + ty;
            if ((node_info1[tx] < cutoff) && (node_info2[ty] < cutoff)) {
                p[ind] = 0.0f;
            } else {
                p[ind] = node_info1[tx] * node_info2[ty];
            }
        }
    }
}

int main() {
    // Test case 1: All values below cutoff
    {
        const int n1 = 3, n2 = 3;
        float node1[n1] = {0.1f, 0.2f, 0.3f};
        float node2[n2] = {0.1f, 0.2f, 0.3f};
        float p[n1 * n2];
        float expected[n1 * n2] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
        
        create_p_vect(node1, node2, p, n1, n2);
        
        for (int i = 0; i < n1 * n2; ++i) {
            assert(p[i] == expected[i]);
        }
    }

    // Test case 2: All values above cutoff
    {
        const int n1 = 2, n2 = 2;
        float node1[n1] = {0.6f, 0.7f};
        float node2[n2] = {0.6f, 0.7f};
        float p[n1 * n2];
        float expected[n1 * n2] = {0.36f, 0.42f, 0.42f, 0.49f};
        
        create_p_vect(node1, node2, p, n1, n2);
        
        for (int i = 0; i < n1 * n2; ++i) {
            assert(p[i] == expected[i]);
        }
    }

    // Test case 3: Mixed values
    {
        const int n1 = 4, n2 = 3;
        float node1[n1] = {0.1f, 0.6f, 0.4f, 0.8f};
        float node2[n2] = {0.3f, 0.7f, 0.1f};
        float p[n1 * n2];
        float expected[n1 * n2] = {0.0f, 0.0f, 0.0f, 0.18f, 0.42f, 0.06f, 0.12f, 0.28f, 0.04f, 0.24f, 0.56f, 0.08f};
        
        create_p_vect(node1, node2, p, n1, n2);
        
        for (int i = 0; i < n1 * n2; ++i) {
            assert(p[i] == expected[i]);
        }
    }

    // Test case 4: Single node
    {
        const int n1 = 1, n2 = 1;
        float node1[n1] = {0.4f};
        float node2[n2] = {0.6f};
        float p[n1 * n2];
        float expected[n1 * n2] = {0.24f};
        
        create_p_vect(node1, node2, p, n1, n2);
        
        for (int i = 0; i < n1 * n2; ++i) {
            assert(p[i] == expected[i]);
        }
    }

    // Test case 5: Empty nodes
    {
        const int n1 = 0, n2 = 0;
        float* node1 = nullptr;
        float* node2 = nullptr;
        float* p = nullptr;
        
        create_p_vect(node1, node2, p, n1, n2);
        // No assertion as function should handle empty arrays gracefully
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}