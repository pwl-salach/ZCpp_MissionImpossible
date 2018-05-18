//
// Created by Salach on 25.03.2018.
//

#include <cmath>
#include "SampledLine.h"

SampledLine::SampledLine(const Point &beginning, const Point &end, uint16_t samplesCount) {
    if(beginning.sameXCoordinate(end)){
        for (int i = 0; i < samplesCount; i++) {
            float yStep = std::fabs(end.getY() - beginning.getY())/samplesCount;
            Point temp = Point(beginning.getX(), beginning.getY() + i*yStep);
            samples.push_back(temp);
        }
    } else {
        calculateFactorA(beginning, end);
        calculateFactorB(beginning, end);
        float xStep = (end.getX() - beginning.getX())/samplesCount;
        for (int i = 0; i < samplesCount; i++) {
            auto x = beginning.getX() + i*xStep;
            auto y = calculate(x);
            Point temp = Point(x, y);
            samples.push_back(temp);
        }
    }
}

Point SampledLine::getNthSample(uint16_t n) {
    return samples.at(n);
}

const std::vector<Point> &SampledLine::getSamples() const {
    return samples;
}
