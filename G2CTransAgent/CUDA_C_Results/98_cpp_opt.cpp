// Optimized code(id = 98): 

void clearLabel(float* prA, float* prB, unsigned int num_nodes, float base) {
    for (unsigned int id = 0; id < num_nodes; ++id) {
        prA[id] = base + prA[id] * 0.85f;
        prB[id] = 0.0f;
    }
}