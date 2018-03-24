//
// Created by salach on 3/1/18.
//

#include "Person.h"
#include <cmath>

Person::~Person() = default;

void Person::setRotation(uint16_t rot) {
    this->rotation = rot;
}

Person::Person() {
    this->movement = Movement::NONE;
    this->turning = Movement::NONE;
    this->sizeX = 30;
    this->sizeY = 18;
}

void Person::setPosition(const Point &pos) {
    this->position = pos;
}


void Person::setMovement(Person::Movement movement) {
    Person::movement = movement;
}

void Person::move() {
    this->rotation = calculateNewRotation();
    this->position  = calculateNewPosition();
}

void Person::setTurning(Person::Movement turning) {
    Person::turning = turning;
}

Point Person::calculateNewPosition() {
    return this->calculateNewPosition(this->rotation);
}

Point Person::calculateNewPosition(uint16_t rot) {
    if (this->movement == Movement::NONE)
        return this->position;
    auto speed = (this->movement == Movement::FORWARD) ? this->movementSpeed : this->movementSpeed/2;
    auto xStep = speed * sin(rot * M_PI / 180);
    auto yStep = speed * cos(rot * M_PI / 180);
    if(this->movement == Movement::FORWARD){
        return {this->position.getX() + xStep, this->position.getY() - yStep};
    } else if (this->movement == Movement::BACK){
        return {this->position.getX() - xStep, this->position.getY() + yStep};
    }
}

uint16_t Person::calculateNewRotation() {
    if(this->turning == Movement::NONE){
        return this->rotation;
    }
    uint16_t full  = 360;
    if(this->turning == Movement::TURN_LEFT){
        return (this->rotation > 0) ? this->rotation - this->turningSpeed : full - this->turningSpeed;
    } else {
        return (this->rotation < 360) ? this->rotation + this->turningSpeed : this->turningSpeed;
    }
}
