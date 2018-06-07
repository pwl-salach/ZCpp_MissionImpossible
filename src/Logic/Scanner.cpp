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

std::vector<std::vector<Point>> Scanner::search(const Map *map, Agent *agent, Point &playerPosition) {
    recalculateAttachmentPosition(agent);
    auto steps = static_cast<uint16_t>(range / 3);
    std::vector<std::vector<Point> > foundObstacles;
    std::vector<Point> obstacleOutline;
    Point prevPoint;
    bool playerFound = false;
    for (int act = -angle / 2; act <= angle / 2; act++) {
        Point maxRangePoint = calculateMaxRangePoint(position, agent->getRotation() + act);
        auto ray = SampledLine(position, maxRangePoint, steps);
        for (auto point : ray.getSamples()) {
            bool visibilityBlocked = false;
            for (auto obstacle : map->getObstacles()) {
                if (map->isPointInsideObstacle(point, obstacle)) {
                    bool obstacleFound = false;
                    if (obstacle->blockingView()) {
                        visibilityBlocked = true;
                        obstacleFound = true;
                    }
                    if (obstacle->blockingMovement()) {
                        if (prevPoint.isSet() && !map->areClose(prevPoint, point, 30.0)) {
                            foundObstacles.push_back(obstacleOutline);
                            obstacleOutline.clear();
                        }
                        obstacleOutline.push_back(point);
                        obstacleFound = true;
                    }
                    if (obstacleFound) {
                        break;
                    }
                }
            }
            if (!playerFound) {
                if (map->isPointThePlayerPosition(point)) {
                    playerPosition = point;
                    playerFound = true;
                }
            }
            if (visibilityBlocked) {
                break;
            }
            prevPoint = point;
        }
    }
    foundObstacles.push_back(obstacleOutline);
    return foundObstacles;
}

Point Scanner::calculateMaxRangePoint(const Point &beginning, int rotation) {
    auto finalXCoord = beginning.getX() + range * std::sin(static_cast<float>(rotation * M_PI) / 180);
    auto finalYCoord = beginning.getY() - range * std::cos(static_cast<float>(rotation * M_PI) / 180);
    return {finalXCoord, finalYCoord};
}

void Scanner::recalculateAttachmentPosition(Agent *agent) {
    auto finalXCoord = (agent->getPosition().getX() +
                        agent->getSizeY() / 2 * std::sin(static_cast<float>(agent->getRotation() * M_PI ) / 180));
    auto finalYCoord = (agent->getPosition().getY() -
                        agent->getSizeY() / 2 * std::cos(static_cast<float>(agent->getRotation() * M_PI ) / 180));
    position = Point(finalXCoord, finalYCoord);
}
