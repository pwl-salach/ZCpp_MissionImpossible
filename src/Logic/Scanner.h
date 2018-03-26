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
#include "PhysicalObject.h"

class Map;

/*!
 * \brief Objects of this class represents way that agents see in this game
 * \sa Agent
 */
class Scanner {
public:
    Scanner(uint16_t pRange, uint8_t pAngle);

    std::vector<PhysicalObject *> searchForObstacles(const Map *map, Point position, uint16_t rotation);
    Point calculateMaxRangePoint(const Point &beginning, uint16_t rotation);
    Point findPlayerPosition(const Map *map, const Point &agentPosition, uint16_t rotation);

private:
    uint16_t range;
    uint8_t angle;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
