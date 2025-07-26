// original code(id = 144): 
 /*
__global__ void kmeans_set_zero ( int * means ) { means [ blockIdx . x * blockDim . x + threadIdx . x ] = 0 ; }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void kmeans_set_zero(int* means, int num_elements) {
    for (int i = 0; i < num_elements; ++i) {
        means[i] = 0;
    }
}

int main() {
    // Test case 1: Normal case with multiple elements
    int arr1[5] = {1, 2, 3, 4, 5};
    kmeans_set_zero(arr1, 5);
    for (int i = 0; i < 5; ++i) {
        assert(arr1[i] == 0);
    }

    // Test case 2: Single element array
    int arr2[1] = {42};
    kmeans_set_zero(arr2, 1);
    assert(arr2[0] == 0);

    // Test case 3: Empty array (should handle gracefully)
    int* arr3 = nullptr;
    kmeans_set_zero(arr3, 0);
    // No assertion as function should handle num_elements=0 without crashing

    // Test case 4: Large array
    const int large_size = 1000;
    int* arr4 = new int[large_size];
    for (int i = 0; i < large_size; ++i) {
        arr4[i] = i + 1;
    }
    kmeans_set_zero(arr4, large_size);
    for (int i = 0; i < large_size; ++i) {
        assert(arr4[i] == 0);
    }
    delete[] arr4;

    // Test case 5: Array with negative values
    int arr5[4] = {-1, -2, -3, -4};
    kmeans_set_zero(arr5, 4);
    for (int i = 0; i < 4; ++i) {
        assert(arr5[i] == 0);
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}