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

class Map;
class Agent;

/*!
 * \brief Objects of this class represents way that agents see in this game
 * \sa Agent
 */
class Scanner {
public:
    Scanner(uint16_t pRange, uint8_t pAngle);
    std::vector<Obstacle *> search(const Map *map, Agent *agent, Point &playerPosition);
private:
    Point position;
    Point centralMaxRangePoint;
    Point leftMaxRangePoint;
    Point rightMaxRangePoint;
    uint16_t range;
    uint8_t angle;

    void recalculateCentralMaxRangePoint(uint16_t rotation);
    void recalculateLeftMaxRangePoint(uint16_t rotation);
    void recalculateRightMaxRangePoint(uint16_t rotation);
    Point calculateMaxRangePoint(const Point &beginning, uint16_t rotation);

    void recalculateAttachmentPosition(Agent *agent);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
