//
// Created by salach on 3/1/18.
//

#include "Scanner.h"
#include "SampledLine.h"
#include "Map.h"
#include <cmath>

Scanner::Scanner(uint16_t pRange, uint8_t pAngle) {
    range = pRange;
    angle = pAngle;
}

std::vector<PhysicalObject *> Scanner::searchForObstacles(const Map *map, Point position, uint16_t rotation) {
    return std::vector<PhysicalObject *>();
}

Point Scanner::findPlayerPosition(const Map *map, const Point &agentPosition, uint16_t rotation) {
    Point centralFinalPoint = calculateMaxRangePoint(agentPosition, rotation);
    uint16_t leftAngle = rotation - angle;
    if(rotation < angle){
        leftAngle = (uint16_t)360 - (angle - rotation);
    }
    Point leftFinalPoint = calculateMaxRangePoint(agentPosition, leftAngle);
    uint16_t rightAngle = rotation + angle;
    if(rotation > 360 - angle){
        rightAngle = angle - rotation;
    }
    Point rightFinalPoint = calculateMaxRangePoint(agentPosition, rightAngle);
    auto steps = static_cast<uint16_t>(range / 2);
    SampledLine centralLine = SampledLine(agentPosition, centralFinalPoint, steps);
    SampledLine leftLine = SampledLine(agentPosition, leftFinalPoint, steps);
    SampledLine rightLine = SampledLine(agentPosition, rightFinalPoint, steps);
    for(uint16_t i = 0; i < steps; i++){
        Point centralSample = centralLine.getNthSample(i);
        Point leftSample = leftLine.getNthSample(i);
        Point rightSample = rightLine.getNthSample(i);
        auto stepSamplesCount = static_cast<uint16_t>(2 + i/2);
        SampledLine leftScanLine = SampledLine(centralSample, leftSample, stepSamplesCount);
        for(auto point : leftScanLine.getSamples()){
            if (map->isPointThePlayerPosition(point)){
                return point;
            }
        }
        SampledLine rightScanLine = SampledLine(centralSample, rightSample, stepSamplesCount);
        for(auto point : rightScanLine.getSamples()){
            if (map->isPointThePlayerPosition(point)){
                return point;
            }
        }
    }
    return Point();
}

Point Scanner::calculateMaxRangePoint(const Point &beginning, uint16_t rotation){
    auto finalXCoord = beginning.getX() + range * sin(rotation * M_PI / 180);
    auto finalYCoord = beginning.getY() - range * cos(rotation * M_PI / 180);
    return Point(finalXCoord, finalYCoord);
}
