//
// Created by salach on 3/1/18.
//

#include "Scanner.h"
#include "SampledLine.h"
#include "Agent.h"
#include "Map.h"
#include <cmath>
#include <algorithm>

Scanner::Scanner(uint16_t pRange, uint8_t pAngle) {
    range = pRange;
    angle = pAngle;
}

std::vector<Obstacle *> Scanner::searchForObstacles(const Map *map, Agent *agent, Point &playerPosition) {
    recalculateAttachmentPosition(agent);
    recalculateCentralMaxRangePoint(agent->getRotation());
    recalculateRightMaxRangePoint(agent->getRotation());
    recalculateLeftMaxRangePoint(agent->getRotation());
    auto steps = static_cast<uint16_t>(range / 3);
    SampledLine centralLine = SampledLine(position, centralMaxRangePoint, steps);
    SampledLine leftLine = SampledLine(position, leftMaxRangePoint, steps);
    SampledLine rightLine = SampledLine(position, rightMaxRangePoint, steps);
    std::vector<Obstacle*> retObstacles;
    for(uint16_t i = 1; i < steps; i++){
        Point centralSample = centralLine.getNthSample(i);
        Point leftSample = leftLine.getNthSample(i);
        Point rightSample = rightLine.getNthSample(i);
        auto stepSamplesCount = static_cast<uint16_t>(2 + i/3);

        auto findPlayerPosition = [&](Point &otherPoint)->bool{
            SampledLine scanLine = SampledLine(centralSample, otherPoint, stepSamplesCount);
            for(auto point : scanLine.getSamples()){
                if (map->isPointThePlayerPosition(point)){
                    playerPosition = point;
                }
                for(auto obstacle : map->getObstacles()){
                    if(obstacle == agent) {
                        continue;
                    }
                    if(std::find(retObstacles.begin(), retObstacles.end(), obstacle) != retObstacles.end()) {
                        continue;
                    }
                    if (map->isPointInsideObstacle(point, obstacle)) {
                        retObstacles.push_back(obstacle);
                    }
                }
            }
        };
        findPlayerPosition(leftSample);
        findPlayerPosition(rightSample);
    }
    return retObstacles;
}

void Scanner::recalculateCentralMaxRangePoint(uint16_t rotation) {
    centralMaxRangePoint = calculateMaxRangePoint(position, rotation);
}

void Scanner::recalculateLeftMaxRangePoint(uint16_t rotation) {
    uint16_t leftAngle = rotation - angle;
    if(rotation < angle){
        leftAngle = (uint16_t)360 - (angle - rotation);
    }
    leftMaxRangePoint = calculateMaxRangePoint(position, leftAngle);
}

void Scanner::recalculateRightMaxRangePoint(uint16_t rotation) {
    uint16_t rightAngle = rotation + angle;
    if(rotation > 360 - angle){
        rightAngle = angle - rotation;
    }
    rightMaxRangePoint = calculateMaxRangePoint(position, rightAngle);
}

Point Scanner::calculateMaxRangePoint(const Point &beginning, uint16_t rotation){
    auto finalXCoord = beginning.getX() + range * sin(rotation * M_PI / 180);
    auto finalYCoord = beginning.getY() - range * cos(rotation * M_PI / 180);
    return Point(finalXCoord, finalYCoord);
}

void Scanner::recalculateAttachmentPosition(Agent *agent) {
    auto finalXCoord = agent->getPosition().getX() + agent->getSizeY()/2 * sin(agent->getRotation()* M_PI / 180);
    auto finalYCoord = agent->getPosition().getY() - agent->getSizeY()/2 * cos(agent->getRotation() * M_PI / 180);
    position = Point(finalXCoord, finalYCoord);
}
