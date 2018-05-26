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
    Point calculateNewPosition(uint16_t rot) override;
    void update();
    bool isPathStackEmpty();
    bool catchPlayer(Player *player);
    void setHeadquarters(Headquarters *headquarters);
    void lookAround(const Map *map);
    void moveAwayFrom(PhysicalObject *pObject);
    bool seesPlayer() const;

    Point getNextDestination();

private:
    void findOtherWay(const Map *map, Obstacle *obstacle);
    double getAlpha(float xDistance, float yDistance) const;
    void reportPlayerPosition(Point &position);

    Scanner scanner;
    std::stack<Point> pathStack;
    Headquarters *headquarters;
    bool visiblePlayer;
    Obstacle *passingObstacle;
    float speed;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
