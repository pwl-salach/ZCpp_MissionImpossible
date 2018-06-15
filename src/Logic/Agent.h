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
    Point calculateNewPosition(uint16_t rot) override;
    void update();
    bool isPathStackEmpty();
    bool catchPlayer(Player *player);
    void setHeadquarters(Headquarters *headquarters);
    void lookAround(const Environment *environment);
    void moveAwayFrom(PhysicalObject *pObject);
    bool seesPlayer() const;
    Point getNextDestination();
    float getSpeed() const;
    const Scanner &getScanner() const;

    const Point &getPassingPoint() const;

private:
    void findOtherWay(const Environment *environment, std::vector<Point> obstacle);
    void updateTheWayAround(const Point &newPassingPoint);
    double getAlpha(float xDistance, float yDistance) const;
    void reportPlayerPosition(Point &position);

    Scanner scanner;
    std::stack<Point> pathStack;
    Headquarters *headquarters;
    bool visiblePlayer;
    Point passingPoint;
    float speed;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
