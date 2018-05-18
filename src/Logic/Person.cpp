//
// Created by salach on 3/1/18.
//

#include "Person.h"
#include <cmath>

Person::~Person() = default;

Person::Person() {
    movement = Movement::NONE;
    turning = Movement::NONE;
    sizeX = 30;
    sizeY = 18;
}

void Person::setMovement(Person::Movement movement) {
    Person::movement = movement;
}

void Person::move() {
    rotation = calculateNewRotation();
    position = calculateNewPosition();
    calculateVerticesPosition();
}

void Person::setTurning(Person::Movement turning) {
    Person::turning = turning;
}

Point Person::calculateNewPosition() {
    return calculateNewPosition(rotation);
}

Point Person::calculateNewPosition(uint16_t rot) {
    if (movement == Movement::NONE)
        return position;
    auto speed = (movement == Movement::FORWARD) ? movementSpeed : movementSpeed/2;
    auto xStep = static_cast<float>(speed * sin(rot * M_PI / 180));
    auto yStep = static_cast<float>(speed * cos(rot * M_PI / 180));
    if(movement == Movement::FORWARD){
        return {position.getX() + xStep, position.getY() - yStep};
    } else if (movement == Movement::BACK){
        return {position.getX() - xStep, position.getY() + yStep};
    }
}

uint16_t Person::calculateNewRotation() {
    if(turning == Movement::NONE){
        return rotation;
    }
    uint16_t full  = 360;
    if(turning == Movement::TURN_LEFT){
        return (rotation > 0) ? rotation - turningSpeed : full - turningSpeed;
    } else {
        return (rotation < 360) ? rotation + turningSpeed : turningSpeed;
    }
}
