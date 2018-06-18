//
// Created by salach on 3/1/18.
//

/*!
 * \file
 * \brief Declaration of the FieldOfView class
 */

#ifndef ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
#define ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H


#include <cstdint>
#include <vector>
#include "Obstacle.h"

class Environment;

class Agent;

/*!
 * \brief Objects of this class represents way that agents see in this game
 * \sa Agent
 */
class Scanner {
public:
    Scanner(uint16_t pRange, uint8_t pAngle);

    std::vector<std::vector<Point>> search(const Environment *environment, Agent *agent, Point &playerPosition);

    const std::vector<Point> &getScannedPoints() const;

private:
    Point calculateMaxRangePoint(const Point &beginning, int rotation);

    void recalculateAttachmentPosition(Agent *agent);

    std::vector<Point> scannedPoints;
    Point position;
    uint16_t range;
    uint8_t angle;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
