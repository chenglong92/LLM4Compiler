// original code(id = 55): 
 /*
__global__ void gpu_add ( float * c , float * a , float * b , int n ) { int j = blockIdx . x * blockDim . x + threadIdx . x ; int m = gridDim . x * blockDim . x ; for ( int k = j ; k < n ; k += m ) { c [ k ] = a [ k ] + b [ k ] ; } }
*/
// optimized code: 

#include <iostream>
#include <limits>
#include <cmath>

void cpu_add(float* c, float* a, float* b, int n) {
    for (int k = 0; k < n; ++k) {
        c[k] = a[k] + b[k];
    }
}

bool compareArrays(float* a, float* b, int n, float epsilon = 1e-6) {
    for (int i = 0; i < n; ++i) {
        if (fabs(a[i] - b[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

void printArray(float* arr, int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void test_case(const char* name, float* a, float* b, float* expected, int n) {
    float* c = new float[n];
    cpu_add(c, a, b, n);
    
    if (compareArrays(c, expected, n)) {
        std::cout << "Test " << name << " PASSED" << std::endl;
    } else {
        std::cout << "Test " << name << " FAILED" << std::endl;
        std::cout << "Expected: ";
        printArray(expected, n);
        std::cout << "Actual:   ";
        printArray(c, n);
    }
    
    delete[] c;
}

int main() {
    // Test case 1: Basic addition
    {
        float a[] = {1.0f, 2.0f, 3.0f};
        float b[] = {4.0f, 5.0f, 6.0f};
        float expected[] = {5.0f, 7.0f, 9.0f};
        test_case("Basic addition", a, b, expected, 3);
    }
    
    // Test case 2: Empty arrays
    {
        float a[] = {};
        float b[] = {};
        float expected[] = {};
        test_case("Empty arrays", a, b, expected, 0);
    }
    
    // Test case 3: Single element
    {
        float a[] = {42.0f};
        float b[] = {-42.0f};
        float expected[] = {0.0f};
        test_case("Single element", a, b, expected, 1);
    }
    
    // Test case 4: Mixed positive and negative
    {
        float a[] = {1.5f, -2.5f, 0.0f};
        float b[] = {-1.0f, 3.0f, 0.0f};
        float expected[] = {0.5f, 0.5f, 0.0f};
        test_case("Mixed positive and negative", a, b, expected, 3);
    }
    
    // Test case 5: Large array
    {
        const int large_n = 1000;
        float* a = new float[large_n];
        float* b = new float[large_n];
        float* expected = new float[large_n];
        
        for (int i = 0; i < large_n; ++i) {
            a[i] = i * 1.0f;
            b[i] = i * 0.5f;
            expected[i] = i * 1.5f;
        }
        
        test_case("Large array", a, b, expected, large_n);
        
        delete[] a;
        delete[] b;
        delete[] expected;
    }
    
    // Test case 6: Float limits
    {
        float max_float = std::numeric_limits<float>::max();
        float min_float = std::numeric_limits<float>::min();
        float a[] = {max_float, min_float, max_float};
        float b[] = {0.0f, min_float, -max_float};
        float expected[] = {max_float, 2*min_float, 0.0f};
        test_case("Float limits", a, b, expected, 3);
    }
    
    // Test case 7: Zero arrays
    {
        float a[] = {0.0f, 0.0f, 0.0f};
        float b[] = {0.0f, 0.0f, 0.0f};
        float expected[] = {0.0f, 0.0f, 0.0f};
        test_case("Zero arrays", a, b, expected, 3);
    }
    
    return 0;
}