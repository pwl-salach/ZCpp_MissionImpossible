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

/*!
 * \brief Objects of this class represents way that agents see in this game
 * \sa Agent
 */
class FieldOfView {
public:
    std::vector<PhysicalObject*> scan();

private:
    uint16_t range;
    uint8_t angle;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
