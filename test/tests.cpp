#include <iostream>
#include "Params/AvailableParameters.h"
#include "Params/ParamArray.hpp"
#include "Params/SceneParams.h"
#include "catch.hpp"

using namespace ParamWorld;

TEST_CASE("Better Param Arrays can use arithmetic", "[ParamArray]")
{
    ParamArray<SP_Count> zeroVec(0.0);
    ParamArray<SP_Count> oneVec(1.0f);
    ParamArray<SP_Count> countVec;

    for (int i = 0; i < SP_Count; i++) {
        countVec[i] = i * 1.0f;
    }

    SECTION("adding 0s and 1s gets 1s")
    {
        ParamArray<SP_Count> sum = zeroVec + oneVec;
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sum[i] == 1.0f);
        }
    }

    SECTION("adding 1s and 1s gets 2s")
    {
        ParamArray<SP_Count> sum = oneVec + oneVec;
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sum[i] == 2.0f);
        }
    }

    SECTION("adding count and count gets doubles")
    {
        ParamArray<SP_Count> sum = countVec + countVec;
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sum[i] == i * 2.0f);
        }
    }

    SECTION("subtracting 1s and count starts at -1")
    {
        ParamArray<SP_Count> diff = countVec - oneVec;
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(diff[i] == i - 1.0f);
        }
    }

    SECTION("multiplying 1s and count gets count")
    {
        ParamArray<SP_Count> prod = countVec.multiplyElement(oneVec);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(prod[i] == i * 1.0f);
        }
    }

    SECTION("multiplying 1s and count gets 0s.")
    {
        ParamArray<SP_Count> prod = countVec.multiplyElement(zeroVec);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(prod[i] == 0.0f);
        }
    }

    SECTION("multiplying count by 2 scalar gets doubles")
    {
        ParamArray<SP_Count> prod = countVec * 2.0f;
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(prod[i] == i * 2.0f);
        }
    }
}

TEST_CASE("Vectors (float arrays) serve as params of SceneParam functions", "[SceneParams]")
{
    srand(0);
    SceneParams sp(0);
    ParamArray<SP_Count> zeros(0.0);
    ParamArray<SP_Count> ones(1.0);
    ParamArray<SP_Count> halves(0.5);

    SECTION("Updated variances after 2 0's should be 0.")
    {
        float startVariances[SP_Count];
        for (int i = 0; i < SP_Count; i++) {
            startVariances[i] = sp.paramVariances[i];
        }
        sp.moveMeans(zeros, true);  // shouldn't change variances at all.
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(startVariances[i] == sp.paramVariances[i]);
        }
        sp.moveMeans(zeros, true);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sp.paramVariances[i] == 0.0);
        }
    }

    // The 0.125 came from direct calculations using algorithm here:
    // https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
    SECTION("Updated variances after a 1 and a .5 should be 0.125")
    {
        sp.moveMeans(ones, true);
        sp.moveMeans(halves, true);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sp.paramVariances[i] == Approx(0.125));
        }
    }

    // The 0.5 came from direct calculations (see above).
    SECTION("Updated variances after a 1 and a 0 should be 0.5")
    {
        sp.moveMeans(ones, true);
        sp.moveMeans(zeros, true);
        for (int i = 0; i < SP_Count; i++) {
            REQUIRE(sp.paramVariances[i] == Approx(0.5));
        }
    }

    SECTION("Learning rate should decrease each time.")
    {
        sp.moveMeans(ones, true);
        sp.moveMeans(zeros, true);
        REQUIRE(sp.learningRate == Approx(0.75f * .999 * .999));
    }
}
