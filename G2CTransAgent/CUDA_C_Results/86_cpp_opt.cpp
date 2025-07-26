// Optimized code(id = 86): 

void kmeans_average(int* means, int* counts, int num_clusters, int dimensions) {
    for (int cluster = 0; cluster < num_clusters; ++cluster) {
        for (int dim = 0; dim < dimensions; ++dim) {
            int idx = cluster * dimensions + dim;
            if (counts[cluster] == 0) {
                means[idx] = 0;
            } else {
                means[idx] /= counts[cluster];
            }
        }
    }
}