#include <gtest/gtest.h>
#include "ParallelGradientAscent1D.hpp"
#include "ParallelGradient1DConfig.hpp"
#include "GradientAscent1D.hpp"
#include "Gradient1DConfig.hpp"
#include "FunctionArgs.hpp"
#include <tuple>
#include <vector>

using namespace std;

static tuple<float, float> evalFunction(float x, FunctionArgs* args) {
    return make_tuple(1 - x*x, -0.5 * x);
}

TEST(ParallelGradientAscent1D, execute) {
    FunctionArgs args;
    ParallelGradient1DConfig config;

    config.GA1DConfig.emplace_back(&evalFunction, &args, -1, -1.1,
                            0.01, 0.01, 0.5, 0.01, 100, 1, 0.001);
    config.GA1DConfig.emplace_back(&evalFunction, &args, 1, 1.1,
                            0.01, 0.01, 0.5, 0.01, 100, 1, 0.001);

    config.xCombineThresh = 0.1;
    

    ParallelGradientAscent1D pga(&config);


    pga.execute();

    EXPECT_NEAR(pga.getMaxValues().at(0), 1, 0.01);
    EXPECT_NEAR(pga.getMaxXValues().at(0), 0, 0.1);
    EXPECT_EQ(pga.getMaxValues().size(), 1);
}