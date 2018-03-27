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
#include "Scanner.h"
#include "Obstacle.h"

class Headquarters;

/*!
 * \brief Objects of this class are meant to find Player
 */
class Agent : public Person, public Obstacle{
public:
    Agent(uint16_t rangeOfView, uint8_t angleOfView);
    void updatePlayerPosition(const Point &newPosition);
    void updateOrders(const Point &destination);
    void addDestination(const Point &point);
    void update();
    bool emptyPathStack();
    bool catchPlayer(Player *player);
    void setHeadquarters(Headquarters *headquarters);

    void lookAround(const Map *map);

private:
    void goToNextDestination();
    void findOtherWay();
    Scanner scanner;
    std::stack<Point> pathStack;
    Headquarters *headquarters;
    Point playerPosition;

    void reportPlayerPosition(Point &position);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
