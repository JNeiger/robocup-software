#pragma once

#include <Geometry2d/Point.hpp>
#include <functional>

class NelderMead2DConfig {
public:
    /**
     * Creates a Nelder-Mead 2D Config
     *
     * @param f std function pointer which returns F(X, Y)
     * @param start starting point of the simplex (Triangle in 2D Case)
     * @param step starting step magnitudes in X, Y directions
     * @param minDist minimum distance of bounding box before exit
     * @param reflectionCoeff perecent to reflect by in the oposite direction
     *           Must be greater than 0
     * @param expansionCoeff percent to extend single point by
     *           Must be greater than 1
     * @param contractionCoeff percent to contract single point by
     *           Must be greater than 0 and less than or equal to 0.5
     * @param shrinkCoeff percent to shrink all points by
     *           Must be between 0 and 1
     * @param maxIterations maximum number of iterations to reach before end
     * @param maxValue max value to exit early at
     * @param maxThresh threshold for the max vlaue before exit
     */
    NelderMead2DConfig(std::function<float(Geometry2d::Point)>* f,
                       Geometry2d::Point start,
                       Geometry2d::Point step,
                       Geometry2d::Point minDist,
                       float reflectionCoeff,
                       float expansionCoeff,
                       float contractionCoeff,
                       float shrinkCoeff,
                       int maxIterations,
                       float maxValue, float maxThresh)
        :
            f(f),
            start(start),
            step(step),
            minDist(minDist),
            reflectionCoeff(reflectionCoeff),
            expansionCoeff(expansionCoeff),
            contractionCoeff(contractionCoeff),
            shrinkCoeff(shrinkCoeff),
            maxIterations(maxIterations),
            maxValue(maxValue),
            maxThresh(maxThresh) {}

    // NelderMead2DConfig(const NelderMead2DConfig*& other) {
    //     f = other->f;
    //     start = other->start;
    //     step = other->step;
    //     minDist = other->minDist;
    //     reflectionCoeff = other->reflectionCoeff;
    //     expansionCoeff = other->expansionCoeff;
    //     contractionCoeff = other->contractionCoeff;
    //     shrinkCoeff = other->shrinkCoeff;
    //     maxIterations = other->maxIterations;
    //     maxValue = other->maxValue;
    //     maxThresh = other->maxThresh;
    // }

    std::function<float(Geometry2d::Point)>* f;
    Geometry2d::Point start;
    Geometry2d::Point step;
    Geometry2d::Point minDist;
    float reflectionCoeff;
    float expansionCoeff;
    float contractionCoeff;
    float shrinkCoeff;
    int maxIterations;
    float maxValue;
    float maxThresh;
};