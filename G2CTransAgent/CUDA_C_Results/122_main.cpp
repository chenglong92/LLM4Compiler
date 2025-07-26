// original code(id = 122): 
 /*
__global__ void invalidateFlow_kernel ( float * modFlowX , float * modFlowY , const float * constFlowX , const float * constFlowY , int width , int height , float cons_thres ) { const int x = blockIdx . x * blockDim . x + threadIdx . x ; const int y = blockIdx . y * blockDim . y + threadIdx . y ; if ( x < width && y < height ) { int ind = y * width + x ; float mFX = modFlowX [ ind ] ; float mFY = modFlowY [ ind ] ; float cFX = constFlowX [ ind ] ; float cFY = constFlowY [ ind ] ; float err = ( mFX - cFX ) * ( mFX - cFX ) + ( mFY - cFY ) * ( mFY - cFY ) ; if ( err > cons_thres ) { mFX = 0 ; mFY = 0 ; } modFlowX [ ind ] = mFX ; modFlowY [ ind ] = mFY ; } }
*/
// optimized code: 

#include <iostream>
#include <cmath>
#include <cassert>

void invalidateFlow(float* modFlowX, float* modFlowY, const float* constFlowX, const float* constFlowY, int width, int height, float cons_thres) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int ind = y * width + x;
            float mFX = modFlowX[ind];
            float mFY = modFlowY[ind];
            float cFX = constFlowX[ind];
            float cFY = constFlowY[ind];
            float err = (mFX - cFX) * (mFX - cFX) + (mFY - cFY) * (mFY - cFY);
            if (err > cons_thres) {
                mFX = 0;
                mFY = 0;
            }
            modFlowX[ind] = mFX;
            modFlowY[ind] = mFY;
        }
    }
}

void test_invalidateFlow() {
    // Test case 1: No modification needed (err <= cons_thres)
    {
        const int width = 2;
        const int height = 2;
        float modFlowX[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float modFlowY[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float constFlowX[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float constFlowY[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float cons_thres = 1.0f;

        invalidateFlow(modFlowX, modFlowY, constFlowX, constFlowY, width, height, cons_thres);

        for (int i = 0; i < width * height; ++i) {
            assert(modFlowX[i] == constFlowX[i]);
            assert(modFlowY[i] == constFlowY[i]);
        }
    }

    // Test case 2: Modification needed (err > cons_thres)
    {
        const int width = 2;
        const int height = 2;
        float modFlowX[width * height] = {2.0f, 3.0f, 4.0f, 5.0f};
        float modFlowY[width * height] = {2.0f, 3.0f, 4.0f, 5.0f};
        float constFlowX[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float constFlowY[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float cons_thres = 1.0f;

        invalidateFlow(modFlowX, modFlowY, constFlowX, constFlowY, width, height, cons_thres);

        for (int i = 0; i < width * height; ++i) {
            assert(modFlowX[i] == 0.0f);
            assert(modFlowY[i] == 0.0f);
        }
    }

    // Test case 3: Mixed case (some modified, some not)
    {
        const int width = 2;
        const int height = 2;
        float modFlowX[width * height] = {1.0f, 2.1f, 3.0f, 5.0f};
        float modFlowY[width * height] = {1.0f, 2.1f, 3.0f, 5.0f};
        float constFlowX[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float constFlowY[width * height] = {1.0f, 2.0f, 3.0f, 4.0f};
        float cons_thres = 0.5f;

        invalidateFlow(modFlowX, modFlowY, constFlowX, constFlowY, width, height, cons_thres);

        assert(modFlowX[0] == 1.0f);
        assert(modFlowY[0] == 1.0f);
        assert(modFlowX[1] == 0.0f);
        assert(modFlowY[1] == 0.0f);
        assert(modFlowX[2] == 3.0f);
        assert(modFlowY[2] == 3.0f);
        assert(modFlowX[3] == 0.0f);
        assert(modFlowY[3] == 0.0f);
    }

    // Test case 4: Edge case with zero threshold
    {
        const int width = 2;
        const int height = 1;
        float modFlowX[width * height] = {0.1f, 0.0f};
        float modFlowY[width * height] = {0.1f, 0.0f};
        float constFlowX[width * height] = {0.0f, 0.0f};
        float constFlowY[width * height] = {0.0f, 0.0f};
        float cons_thres = 0.0f;

        invalidateFlow(modFlowX, modFlowY, constFlowX, constFlowY, width, height, cons_thres);

        assert(modFlowX[0] == 0.0f);
        assert(modFlowY[0] == 0.0f);
        assert(modFlowX[1] == 0.0f);
        assert(modFlowY[1] == 0.0f);
    }

    // Test case 5: Single element array
    {
        const int width = 1;
        const int height = 1;
        float modFlowX[width * height] = {1.0f};
        float modFlowY[width * height] = {1.0f};
        float constFlowX[width * height] = {0.0f};
        float constFlowY[width * height] = {0.0f};
        float cons_thres = 1.0f;

        invalidateFlow(modFlowX, modFlowY, constFlowX, constFlowY, width, height, cons_thres);

        assert(modFlowX[0] == 0.0f);
        assert(modFlowY[0] == 0.0f);
    }
}

int main() {
    test_invalidateFlow();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}