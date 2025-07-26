// original code(id = 31): 
 /*
__global__ void sum_arrays_gpu ( int * a , int * b , int * c , int size ) { int index = blockDim . x * blockIdx . x + threadIdx . x ; if ( index < size ) c [ index ] = a [ index ] + b [ index ] ; }
*/
// optimized code: 

#include <iostream>
        #include <cassert>
        #include <climits>
        #include <vector>
        #include <random>

        void sum_arrays_cpu(int* a, int* b, int* c, int size) {
            for (int index = 0; index < size; ++index) {
                c[index] = a[index] + b[index];
            }
        }

        void test_sum_arrays() {
            // Test case 1: Small arrays with positive numbers
            {
                int a[] = {1, 2, 3};
                int b[] = {4, 5, 6};
                int c[3];
                int expected[] = {5, 7, 9};
                sum_arrays_cpu(a, b, c, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 2: Arrays with negative numbers
            {
                int a[] = {-1, -2, -3};
                int b[] = {4, 5, 6};
                int c[3];
                int expected[] = {3, 3, 3};
                sum_arrays_cpu(a, b, c, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 3: Arrays with zeros
            {
                int a[] = {0, 0, 0};
                int b[] = {0, 0, 0};
                int c[3];
                int expected[] = {0, 0, 0};
                sum_arrays_cpu(a, b, c, 3);
                for (int i = 0; i < 3; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            // Test case 4: Single element arrays
            {
                int a[] = {42};
                int b[] = {58};
                int c[1];
                int expected[] = {100};
                sum_arrays_cpu(a, b, c, 1);
                assert(c[0] == expected[0]);
            }

            // Test case 5: Integer overflow case
            {
                int a[] = {INT_MAX, INT_MIN};
                int b[] = {1, -1};
                int c[2];
                sum_arrays_cpu(a, b, c, 2);
                assert(c[0] == INT_MIN); // INT_MAX + 1 wraps around to INT_MIN
                assert(c[1] == INT_MAX); // INT_MIN + (-1) wraps around to INT_MAX
            }

            // Test case 6: Empty arrays
            {
                int a[] = {};
                int b[] = {};
                int c[] = {};
                sum_arrays_cpu(a, b, c, 0);
                // No operation should be performed
            }

            // Test case 7: Large arrays
            {
                const int size = 10000;
                std::vector<int> a(size, 1);
                std::vector<int> b(size, 2);
                std::vector<int> c(size);
                sum_arrays_cpu(a.data(), b.data(), c.data(), size);
                for (int i = 0; i < size; ++i) {
                    assert(c[i] == 3);
                }
            }

            // Test case 8: Random arrays
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(-1000, 1000);

                const int size = 1000;
                std::vector<int> a(size);
                std::vector<int> b(size);
                std::vector<int> expected(size);
                std::vector<int> c(size);

                for (int i = 0; i < size; ++i) {
                    a[i] = distrib(gen);
                    b[i] = distrib(gen);
                    expected[i] = a[i] + b[i];
                }

                sum_arrays_cpu(a.data(), b.data(), c.data(), size);
                for (int i = 0; i < size; ++i) {
                    assert(c[i] == expected[i]);
                }
            }

            std::cout << "All tests passed successfully!\n";
        }

        int main() {
            test_sum_arrays();
            return 0;
        }