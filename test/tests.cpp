#include "catch.hpp"
#include "Params/SceneParams.h"
#include "Params/AvailableParameters.h"

using namespace ParamWorld;
TEST_CASE( "Vectors (float arrays) can work with arthmetic", "[SceneParams]" ) {
    float *zeroVec = (float *)malloc(sizeof(float) * SP_Count);
    float *oneVec = (float *)malloc(sizeof(float) * SP_Count);
    float *countVec = (float *)malloc(sizeof(float) * SP_Count);

    for (int i = 0; i < SP_Count; i++ ) {
        zeroVec[i] = 0.0f;
        oneVec[i] = 1.0f;
        countVec[i] = i * 1.0f;
    }

    SceneParams sp;

    SECTION("adding 0s and 1s gets 1s") {
        float *sum = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectAdd(zeroVec, oneVec, sum);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( sum[i] == 1.0f);
        }
    }

    SECTION("adding 1s and 1s gets 1s") {
        float *sum = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectAdd(oneVec, oneVec, sum);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( sum[i] == 2.0f);
        }

    }
}
