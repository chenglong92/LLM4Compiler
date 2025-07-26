// original code(id = 86): 
 /*
__global__ void kmeans_average ( int * means , int * counts ) { if ( counts [ blockIdx . x ] == 0 ) means [ blockIdx . x * blockDim . x + threadIdx . x ] = 0 ; else means [ blockIdx . x * blockDim . x + threadIdx . x ] /= counts [ blockIdx . x ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>

        void kmeans_average(int* means, int* counts, int num_clusters, int dimensions);

        void test_kmeans_average() {
            // Test case 1: Single cluster, single dimension, count non-zero
            {
                int means[] = {10};
                int counts[] = {5};
                int num_clusters = 1;
                int dimensions = 1;
                
                kmeans_average(means, counts, num_clusters, dimensions);
                
                assert(means[0] == 2);  // 10 / 5 = 2
            }

            // Test case 2: Single cluster, single dimension, count zero
            {
                int means[] = {10};
                int counts[] = {0};
                int num_clusters = 1;
                int dimensions = 1;
                
                kmeans_average(means, counts, num_clusters, dimensions);
                
                assert(means[0] == 0);  // count is 0, should set to 0
            }

            // Test case 3: Multiple clusters, multiple dimensions, mixed counts
            {
                int means[] = {10, 20, 30, 40, 50, 60};
                int counts[] = {2, 0, 5};
                int num_clusters = 3;
                int dimensions = 2;
                
                kmeans_average(means, counts, num_clusters, dimensions);
                
                // Cluster 0: 10/2=5, 20/2=10
                // Cluster 1: 30/0=0, 40/0=0
                // Cluster 2: 50/5=10, 60/5=12
                assert(means[0] == 5);
                assert(means[1] == 10);
                assert(means[2] == 0);
                assert(means[3] == 0);
                assert(means[4] == 10);
                assert(means[5] == 12);
            }

            // Test case 4: Two clusters, three dimensions
            {
                int means[] = {9, 18, 27, 0, 0, 0};
                int counts[] = {3, 0};
                int num_clusters = 2;
                int dimensions = 3;
                
                kmeans_average(means, counts, num_clusters, dimensions);
                
                // Cluster 0: 9/3=3, 18/3=6, 27/3=9
                // Cluster 1: all 0
                assert(means[0] == 3);
                assert(means[1] == 6);
                assert(means[2] == 9);
                assert(means[3] == 0);
                assert(means[4] == 0);
                assert(means[5] == 0);
            }

            std::cout << "All test cases passed!" << std::endl;
        }

        int main() {
            test_kmeans_average();
            return 0;
        }

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