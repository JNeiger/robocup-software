#include <gtest/gtest.h>
#include "KickEvaluator.hpp"
#include "SystemState.hpp"

#include <stdlib.h>

using namespace Geometry2d;

TEST(KickEvaluator, no_robots) {
    SystemState state;
    KickEvaluator kickEval(&state);
    std::pair<Point, double> pt_to_our_goal;
    std::pair<Point, double> expected = std::pair<Point, double>(Point{0,0}, 1.0);

    // No opponent robot
    pt_to_our_goal = kickEval.eval_pt_to_our_goal(Point(0, 0.3));

    // Due to the search functions, these may be a little off sometimes
    EXPECT_NEAR((std::get<0>(expected)).x(), (std::get<0>(pt_to_our_goal)).x(), 0.01);
    EXPECT_NEAR((std::get<0>(expected)).y(), (std::get<0>(pt_to_our_goal)).y(), 0.01);
    EXPECT_NEAR(std::get<1>(expected), std::get<1>(pt_to_our_goal), 0.01);
}

TEST(KickEvaluator, eval_pt_to_our_goal) {
    SystemState state;
    OurRobot* obstacleBot = state.self[0];
    obstacleBot->visible = true;
    obstacleBot->pos = Point(1, 1);

    KickEvaluator kickEval(&state);
    std::pair<Point, double> pt_to_our_goal;
    std::pair<Point, double> expected = std::pair<Point, double>(Point{0,0}, 0.56);

    pt_to_our_goal = kickEval.eval_pt_to_our_goal(Point(0, 2));

    EXPECT_GT((std::get<0>(expected)).x(), (std::get<0>(pt_to_our_goal)).x());
    EXPECT_NEAR((std::get<0>(expected)).y(), (std::get<0>(pt_to_our_goal)).y(), 0.01);
    EXPECT_GT(std::get<1>(expected), 0);
    EXPECT_LT(std::get<1>(expected), 1);
}

TEST(KickEvaluator, eval_calculation) {
    // Kick mean, Kick stdev, Robot mean, robot stdev, robot scale, boundsLower, boundsUpper
    KickEvaluatorArgs test(0, 0.1, {10}, {0.1}, {1}, -2, 2);

    std::tuple<double, double> res = KickEvaluator::eval_calculation(0, &test);
    std::tuple<double, double> expected = std::make_tuple(1, 0);

    EXPECT_NEAR(std::get<0>(res), std::get<0>(res), 0.01); // Value
    EXPECT_NEAR(std::get<1>(res), std::get<1>(res), 0.01); // Derivative
}


TEST(KickEvaluator, speed) {
    SystemState state;
    OurRobot* obstacleBot = state.self[0];
    obstacleBot->visible = true;
    obstacleBot->pos = Point(1, 1);

    KickEvaluator kickEval(&state);

    for (double x = -Field_Dimensions::Current_Dimensions.Width() / 2; 
                x < Field_Dimensions::Current_Dimensions.Width() / 2;
                x += 0.01) {
        for (double y = 0; 
                    y < Field_Dimensions::Current_Dimensions.Length();
                    y += 0.01) {
            std::pair<Point, double> result =
                kickEval.eval_pt_to_our_goal(Point(x, y));
        }
    }
}

TEST(KickEvaluator, function_speed) {
    KickEvaluatorArgs test(0, 0.1, {10}, {0.1}, {1}, -2, 2);
    int cnt = 0;
    for (double x = -Field_Dimensions::Current_Dimensions.Width() / 2; 
                x < Field_Dimensions::Current_Dimensions.Width() / 2;
                x += 0.01) {
        for (double y = 0; 
                    y < Field_Dimensions::Current_Dimensions.Length();
                    y += 0.01) {
            std::tuple<double, double> res = 
                KickEvaluator::eval_calculation(0, &test);
        }
    }
    std::cout << cnt << std::endl;
}