//
// Created by salach on 3/1/18.
//

#include "Person.h"
#include <math.h>

Person::~Person() {
    this->movement = Movement::NONE;
    this->turning = Movement::NONE;
}

void Person::setRotation(uint16_t rot) {
    this->rotation = rot;
}

Person::Person() {
    this->sizeX = 30;
    this->sizeY = 18;
}

void Person::setPosition(const Point &point) {
    this->positionX = point.getX();
    this->positionY = point.getY();
}


void Person::setMovement(Person::Movement movement) {
    Person::movement = movement;
}

void Person::move() {
    if(this->turning == Movement::TURN_LEFT){
        this->turnLeft();
    } else if (this->turning == Movement::TURN_RIGHT){
        this->turnRight();
    }
    if(this->movement == Movement::FORWARD){
        this->moveForward();
    } else if (this->movement == Movement::BACK){
        this->moveBackward();
    }
}

void Person::moveForward() {
    auto xStep = this->movementSpeed * sin(this->rotation * M_PI / 180);
    auto yStep = this->movementSpeed * cos(this->rotation * M_PI / 180);
    this->positionX += xStep;
    this->positionY -= yStep;
}

void Person::moveBackward() {

}

void Person::turnLeft() {
    uint16_t full  = 360;
    if (this->rotation > 0){
        this->rotation -= this->turningSpeed;
    } else{
        this->rotation = full - this->turningSpeed;
    }
}

void Person::turnRight() {
    if (this->rotation < 360){
        this->rotation += this->turningSpeed;
    } else{
        this->rotation = this->turningSpeed;
    }
}

void Person::setTurning(Person::Movement turning) {
    Person::turning = turning;
}

