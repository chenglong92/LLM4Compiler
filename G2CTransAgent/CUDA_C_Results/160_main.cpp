// original code(id = 160): 
 /*
__global__ void Copy_List ( const int element_numbers , const float * origin_list , float * list ) { int i = blockDim . x * blockIdx . x + threadIdx . x ; if ( i < element_numbers ) { list [ i ] = origin_list [ i ] ; } }
*/
// optimized code: 

#include <iostream>
#include <cassert>

void Copy_List(const int element_numbers, const float* origin_list, float* list) {
    for (int i = 0; i < element_numbers; ++i) {
        list[i] = origin_list[i];
    }
}

int main() {
    // Test case 1: Normal case with multiple elements
    {
        const int element_numbers = 5;
        float origin_list[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
        float list[element_numbers];
        
        Copy_List(element_numbers, origin_list, list);
        
        for (int i = 0; i < element_numbers; ++i) {
            assert(list[i] == origin_list[i]);
        }
    }

    // Test case 2: Single element
    {
        const int element_numbers = 1;
        float origin_list[] = {42.0f};
        float list[element_numbers];
        
        Copy_List(element_numbers, origin_list, list);
        
        assert(list[0] == origin_list[0]);
    }

    // Test case 3: Empty list (should do nothing)
    {
        const int element_numbers = 0;
        float origin_list[] = {};
        float list[] = {};
        
        Copy_List(element_numbers, origin_list, list);
        // No assertion needed as function should do nothing
    }

    // Test case 4: Large number of elements
    {
        const int element_numbers = 1000;
        float origin_list[element_numbers];
        float list[element_numbers];
        
        for (int i = 0; i < element_numbers; ++i) {
            origin_list[i] = static_cast<float>(i);
        }
        
        Copy_List(element_numbers, origin_list, list);
        
        for (int i = 0; i < element_numbers; ++i) {
            assert(list[i] == origin_list[i]);
        }
    }

    // Test case 5: Negative element count (should do nothing)
    {
        const int element_numbers = -5;
        float origin_list[] = {1.0f, 2.0f, 3.0f};
        float list[] = {0.0f, 0.0f, 0.0f};
        
        Copy_List(element_numbers, origin_list, list);
        // No assertion needed as function should do nothing
    }

    std::cout << "All test cases passed!" << std::endl;
    return 0;
}