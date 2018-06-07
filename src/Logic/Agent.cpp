//
// Created by salach on 3/1/18.
//

#include <cmath>
#include "Agent.h"
#include "Headquarters.h"
#include "Line.h"

Agent::Agent(uint16_t rangeOfView, uint8_t angleOfView) : scanner(Scanner(rangeOfView, angleOfView)) {
    movementSpeed = 3;
    turningSpeed = 5;
    imageName = "agent.png";
    visiblePlayer = false;
}

void Agent::addDestination(const Point &point) {
    pathStack.push(point);
}

void Agent::updateOrders(const Point &destination) {
    while (!pathStack.empty()) {
        pathStack.pop();
    }
    pathStack.push(destination);
}

void Agent::update() {
    Point nextDestination = getNextDestination();
    auto xDistance = nextDestination.getX() - position.getX();
    auto yDistance = nextDestination.getY() - position.getY();
    auto alpha = getAlpha(xDistance, yDistance);
    auto distance = std::sqrt(xDistance * xDistance + yDistance * yDistance);
    if (distance > movementSpeed) {
        if (std::fabs(rotation - alpha) < 90) {
            movement = Movement::FORWARD;
        } else {
            movement = Movement::NONE;
            if (turning != Movement::NONE) {
                if (std::fabs(rotation - alpha) < turningSpeed) {
                    turning = Movement::NONE;
                }
                return;
            }
        }
        speed = static_cast<float>((180 - std::fabs(rotation - alpha)) * movementSpeed / 180);
        if (rotation - alpha > turningSpeed) {
            turning = Movement::TURN_LEFT;
        } else if (alpha - rotation > turningSpeed) {
            turning = Movement::TURN_RIGHT;
        } else {
            turning = Movement::NONE;
        }
    } else {
        pathStack.pop();
        if(passingPoint.isSet()){
            passingPoint = Point();
        }
        update();
    }
}

double Agent::getAlpha(float xDistance, float yDistance) const {
    double alpha = std::atan(std::fabs(xDistance) / std::fabs(yDistance)) * 180 / M_PI;
    if (xDistance > 0 && yDistance > 0) {
        alpha = 180 - alpha;
    } else if (xDistance <= 0 && yDistance >= 0) {
        alpha = 180 + alpha;
    } else if (xDistance < 0 && yDistance < 0) {
        alpha = 360 - alpha;
    }
    return alpha;
}

bool Agent::isPathStackEmpty() {
    return pathStack.empty();
}

void Agent::lookAround(const Map *map) {
    Point playerPos;
    auto obstacles = scanner.search(map, this, playerPos);
    if (playerPos.isSet()) {
        reportPlayerPosition(playerPos);
        visiblePlayer = true;
    } else {
        visiblePlayer = false;
    }
    for (const auto &obstacle : obstacles) {
        if (map->blocksTheWay(this, obstacle)) {
            findOtherWay(map, obstacle);
        } else if (passingPoint.isSet()){
            auto closestPoint = map->getClosePoint(passingPoint, obstacle, 30);
            if(closestPoint.isSet()){
                updateTheWayAround(closestPoint);
            }
        }
    }
}

void Agent::reportPlayerPosition(Point &position) {
    headquarters->acceptThePositionReport(position);
}

void Agent::updatePlayerPosition(const Point &newPosition) {
    updateOrders(newPosition);
}

void Agent::setHeadquarters(Headquarters *headquarters) {
    Agent::headquarters = headquarters;
}

bool Agent::catchPlayer(Player *player) {
    auto xDistance = position.getX() - player->getPosition().getX();
    auto yDistance = position.getY() - player->getPosition().getY();
    return std::sqrt(xDistance * xDistance + yDistance * yDistance) <= this->sizeY;
}

void Agent::findOtherWay(const Map *map, std::vector<Point> obstacle) {
    auto nextDest = getNextDestination();
    float minDistance = map->getSizeX();
    for (auto vertex: obstacle) {
        auto posVerDist = map->calculateDistance(position, vertex);
        auto verDestDist = map->calculateDistance(vertex, nextDest);
        auto distance = posVerDist + verDestDist;
        if (distance <= minDistance) {
            minDistance = distance;
            passingPoint = vertex;
        }
    }
    Line line = Line(position, nextDest);
    float correction = 60;
    float xCorrection = 0;
    float yCorrection = 0;
    if (passingPoint.getY() >= line.calculate(passingPoint.getX())) {
        if (passingPoint.getY() >= position.getY() && passingPoint.getY() >= nextDest.getY()) {
            yCorrection = correction;
        }
    } else {
        if (passingPoint.getY() <= position.getY() && passingPoint.getY() <= nextDest.getY()) {
            yCorrection = correction;
        }
    }
    if (yCorrection == 0) {
        if (passingPoint.getX() >= position.getX()) {
            xCorrection = correction;
        } else {
            xCorrection = -correction;
        }
    }
    Point newDest = Point(passingPoint.getX() + xCorrection, passingPoint.getY() + yCorrection);
    pathStack.push(newDest);
}

Point Agent::calculateNewPosition(uint16_t rot) {
    return Person::calculateNewPosition(rot, speed);
}

void Agent::moveAwayFrom(PhysicalObject *pObject) {
    auto xDistance = pObject->getPosition().getX() - position.getX();
    auto yDistance = pObject->getPosition().getY() - position.getY();
    auto alpha = getAlpha(xDistance, yDistance);
    if (rotation >= alpha) {
        turning = Movement::TURN_RIGHT;
    } else {
        turning = Movement::TURN_LEFT;
    }
    speed = static_cast<float>((std::fabs(rotation - alpha) - 45) * movementSpeed / 180);
    move();
}

Point Agent::getNextDestination() {
    if (pathStack.empty()) {
        headquarters->planSearching(this);
    }
    return pathStack.top();
}

bool Agent::seesPlayer() const {
    return visiblePlayer;
}

void Agent::updateTheWayAround(const Point &newPassingPoint) {
    auto xDistance = newPassingPoint.getX() - passingPoint.getX();
    auto yDistance = newPassingPoint.getY() - passingPoint.getY();
    auto dest = pathStack.top();
    pathStack.pop();
    pathStack.push({dest.getX()+xDistance, dest.getY()+yDistance});
}
