// original code(id = 98): 
 /*
__global__ void clearLabel ( float * prA , float * prB , unsigned int num_nodes , float base ) { unsigned int id = blockDim . x * blockIdx . x + threadIdx . x ; if ( id < num_nodes ) { prA [ id ] = base + prA [ id ] * 0.85 ; prB [ id ] = 0 ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void clearLabel(float* prA, float* prB, unsigned int num_nodes, float base) {
    for (unsigned int id = 0; id < num_nodes; ++id) {
        prA[id] = base + prA[id] * 0.85f;
        prB[id] = 0.0f;
    }
}

int main() {
    // Test case 1: Single node
    {
        float prA[1] = {1.0f};
        float prB[1] = {2.0f};
        clearLabel(prA, prB, 1, 0.5f);
        assert(prA[0] == 0.5f + 1.0f * 0.85f);
        assert(prB[0] == 0.0f);
    }

    // Test case 2: Multiple nodes
    {
        float prA[3] = {1.0f, 2.0f, 3.0f};
        float prB[3] = {4.0f, 5.0f, 6.0f};
        clearLabel(prA, prB, 3, 0.1f);
        assert(prA[0] == 0.1f + 1.0f * 0.85f);
        assert(prA[1] == 0.1f + 2.0f * 0.85f);
        assert(prA[2] == 0.1f + 3.0f * 0.85f);
        assert(prB[0] == 0.0f);
        assert(prB[1] == 0.0f);
        assert(prB[2] == 0.0f);
    }

    // Test case 3: Zero nodes
    {
        float prA[1] = {1.0f};
        float prB[1] = {2.0f};
        clearLabel(prA, prB, 0, 0.0f);
        // No change expected since num_nodes is 0
        assert(prA[0] == 1.0f);
        assert(prB[0] == 2.0f);
    }

    // Test case 4: Negative base value
    {
        float prA[2] = {1.0f, 2.0f};
        float prB[2] = {3.0f, 4.0f};
        clearLabel(prA, prB, 2, -0.5f);
        assert(prA[0] == -0.5f + 1.0f * 0.85f);
        assert(prA[1] == -0.5f + 2.0f * 0.85f);
        assert(prB[0] == 0.0f);
        assert(prB[1] == 0.0f);
    }

    // Test case 5: Large number of nodes
    {
        const unsigned int num_nodes = 1000;
        float prA[num_nodes];
        float prB[num_nodes];
        for (unsigned int i = 0; i < num_nodes; ++i) {
            prA[i] = static_cast<float>(i);
            prB[i] = static_cast<float>(i + num_nodes);
        }
        clearLabel(prA, prB, num_nodes, 1.0f);
        for (unsigned int i = 0; i < num_nodes; ++i) {
            assert(prA[i] == 1.0f + static_cast<float>(i) * 0.85f);
            assert(prB[i] == 0.0f);
        }
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}