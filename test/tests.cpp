#include "catch.hpp"
#include "Params/SceneParams.h"
#include "Params/AvailableParameters.h"
#include "Params/ParamArray.hpp"

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

    SECTION("adding 1s and 1s gets 2s") {
        float *sum = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectAdd(oneVec, oneVec, sum);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( sum[i] == 2.0f);
        }
    }

    SECTION("adding count and count gets doubles") {
        float *sum = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectAdd(countVec, countVec, sum);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( sum[i] == i * 2.0f);
        }
    }

    SECTION("subtracting 1s and count starts at -1") {
        float *diff = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectMinus(countVec, oneVec, diff);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( diff[i] == i - 1.0f);
        }
    }

    SECTION("multiplying 1s and count gets count") {
        float *prod = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectProd(countVec, oneVec, prod);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( prod[i] == i * 1.0f);
        }
    }

    SECTION("multiplying 1s and count gets 0s.") {
        float *prod = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectProd(countVec, zeroVec, prod);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( prod[i] == 0.0f);
        }
    }

    SECTION("multiplying count by 2 scalar gets doubles") {
        float *prod = (float *)malloc(sizeof(float) * SP_Count);
        sp.vectProdScalar(countVec, 2.0f, prod);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE( prod[i] == i * 2.0f);
        }
    }
}

TEST_CASE("Better Param Arrays can use arithmetic", "[ParamArray]") {
    ParamArray<5> a;

    SECTION("Accessing the first element of a") {
        a[0];
    }
}
