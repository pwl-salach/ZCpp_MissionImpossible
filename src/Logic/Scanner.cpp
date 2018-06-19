//
// Created by salach on 3/1/18.
//

#include "Scanner.h"
#include "SampledLine.h"
#include "Agent.h"
#include "Environment.h"
#include <cmath>
#include <algorithm>
#include <mutex>

Scanner::Scanner(uint16_t pRange, uint8_t pAngle, Agent *pAgent) {
    range = pRange;
    angle = pAngle;
    agent = pAgent;
}

std::vector<std::vector<Point>> Scanner::search(const Environment *environment, Point &playerPosition) {
    std::mutex guiLock;
    scannedPoints.clear();
    recalculateAttachmentPosition(agent);
    auto steps = static_cast<uint16_t>(range / 4);
    std::vector<std::vector<Point> > foundObstacles;
    std::vector<Point> obstacleOutline;
    Point prevPoint;
    bool playerFound = false;
    for (int act = -angle / 2; act <= angle / 2; act += 2) {
        Point maxRangePoint = calculateMaxRangePoint(position, agent->getRotation() + act);
        auto ray = SampledLine(position, maxRangePoint, steps);
        bool outlineFound = false;
        for (auto point : ray.getSamples()) {
            scannedPoints.push_back(point);
            bool visibilityBlocked = false;
            for (auto obstacle : environment->getObstacles()) {
                if (obstacle == agent) {
                    break;
                }
                if (environment->isPointInsideObstacle(point, obstacle)) {
                    if (obstacle->blockingView()) {
                        visibilityBlocked = true;
                    }
                    if (obstacle->blockingMovement() && !outlineFound) {
                        if (prevPoint.isSet() && !environment->areClose(prevPoint, point, 30.0)) {
                            foundObstacles.push_back(obstacleOutline);
                            obstacleOutline = std::vector<Point>();
                        }
                        obstacleOutline.push_back(point);
                        outlineFound = true;
                    }
                    if (outlineFound || visibilityBlocked) {
                        break;
                    }
                }
            }
            if (!playerFound) {
                if (environment->isPointThePlayerPosition(point)) {
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

const std::vector<Point> &Scanner::getScannedPoints() const {
    return scannedPoints;
}
