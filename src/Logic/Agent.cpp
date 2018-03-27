//
// Created by salach on 3/1/18.
//

#include <cmath>
#include "Agent.h"
#include "Headquarters.h"

Agent::Agent(uint16_t rangeOfView, uint8_t angleOfView): scanner(Scanner(rangeOfView, angleOfView)) {
    movementSpeed = 3;
    turningSpeed = 5;
    imageName = "agent.png";
}

void Agent::addDestination(const Point &point) {
    pathStack.push(point);
}

void Agent::updateOrders(const Point &destination) {
    while(!pathStack.empty()){
        pathStack.pop();
    }
    pathStack.push(destination);
}

void Agent::update() {
    if(pathStack.empty()){
        return;
    }
    Point nextDestination = pathStack.top();
    double alpha = 0;
    auto xDistance = nextDestination.getX() - position.getX();
    auto yDistance = nextDestination.getY() - position.getY();
    alpha = atan(fabs(xDistance)/fabs(yDistance)) * 180 / M_PI;
    if(xDistance > 0 && yDistance > 0){
        alpha = 180 - alpha;
    } else if (xDistance <= 0 && yDistance >= 0){
        alpha = 180 + alpha;
    } else if(xDistance < 0 && yDistance < 0){
        alpha = 360 - alpha;
    }

    auto distance = sqrt(xDistance*xDistance + yDistance*yDistance);
    if(distance > movementSpeed){
        if(fabs(rotation - alpha) < 90){
            movement = Movement::FORWARD;
        } else{
            movement = Movement::NONE;
            if(turning != Movement::NONE) {\
                if (fabs(rotation - alpha) < turningSpeed) {
                    turning = Movement::NONE;
                }
                return;
            }
        }
        if(rotation - alpha > turningSpeed){
            turning = Movement::TURN_LEFT;
        } else if(alpha - rotation > turningSpeed){
            turning = Movement::TURN_RIGHT;
        } else {
            turning = Movement::NONE;
        }
    } else {
        pathStack.pop();
        movement = Movement::NONE;
        turning = Movement::NONE;
    }
}

bool Agent::emptyPathStack() {
    return pathStack.empty();
}

void Agent::lookAround(const Map *map) {
    auto playerPos = scanner.findPlayerPosition(map, position, rotation);
    if(playerPos.isSet()){
        reportPlayerPosition(playerPos);
    }
    auto objects = scanner.searchForObstacles(map, position, rotation);
}

void Agent::reportPlayerPosition(Point &position) {
    headquarters->acceptThePositionReport(position);
}

void Agent::updatePlayerPosition(const Point &newPosition) {
    playerPosition = newPosition;
    updateOrders(playerPosition);
}

void Agent::setHeadquarters(Headquarters *headquarters) {
    Agent::headquarters = headquarters;
}

bool Agent::catchPlayer(Player *player) {
    auto xDistance = position.getX() - player->getPosition().getX();
    auto yDistance = position.getY() - player->getPosition().getY();
    return sqrt(xDistance*xDistance + yDistance*yDistance) <= this->sizeY;
}
