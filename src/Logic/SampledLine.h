//
// Created by Salach on 25.03.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H
#define ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H


#include <vector>
#include "Point.h"
#include "Line.h"

class SampledLine: public Line {
public:
    SampledLine(const Point &beginning, const Point &end, uint16_t samplesCount);

    Point getNthSample(uint16_t n);

    const std::vector<Point> &getSamples() const;

private:
    std::vector<Point> samples;
    float step;
public:
    float getStep() const;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H
