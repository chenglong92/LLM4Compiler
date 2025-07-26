// Optimized code(id = 227): 

#include <iostream>

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

// Example usage:
// int main() {
//     const int n1 = 5, n2 = 5;
//     float node1[n1] = {0.1f, 0.6f, 0.4f, 0.7f, 0.2f};
//     float node2[n2] = {0.3f, 0.8f, 0.5f, 0.9f, 0.1f};
//     float p[n1 * n2];
//     
//     create_p_vect(node1, node2, p, n1, n2);
//     
//     for (int i = 0; i < n1; ++i) {
//         for (int j = 0; j < n2; ++j) {
//             std::cout << p[i * n2 + j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }