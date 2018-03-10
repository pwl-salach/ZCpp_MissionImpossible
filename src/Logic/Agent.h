//
// Created by salach on 3/1/18.
//
/*!
 * \file
 * \brief Declaration of the Agent class
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
#define ZCPP_MISSIONIMPOSSIBLE_AGENTS_H


#include <stack>
#include "Person.h"
#include "Point.h"

class Headquarters;

/*!
 * \brief Objects of this class are meant to find Player
 */
class Agent : public Person {
public:
    Agent(uint16_t posX, uint16_t posY, uint16_t rot);
    void updatePlayerPosition(Point *newPosition);
    void updateOrders(Point* destination);
private:
    void goToNextDestination();
    void findOtherWay();

    std::stack<Point*> pathStack;
    Headquarters *headquarters;
    Point *playerPosition;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
