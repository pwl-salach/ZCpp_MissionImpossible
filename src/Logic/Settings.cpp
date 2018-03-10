//
// Created by salach on 2/28/18.
//

#include "Settings.h"

Settings::Settings() {
    this->mapNumber = 1;
    this->numberOfAgents = 3;
    this->rangeOfView = 128;
    this->angleOfView = 30;
    this->debug = false;

    this->minManNumber = 1;
    this->maxManNumber = 2;
    this->minNumberOfAgents = 1;
    this->maxNumberOfAgents = 6;
    this->minRangeOfView = 50;
    this->maxRangeOfView = 300;
    this->minAngleOfView = 20;
    this->maxAngleOfView = 120;
}

uint8_t Settings::getNumberOfAgents() const {
    return numberOfAgents;
}

uint16_t Settings::getRangeOfView() const {
    return rangeOfView;
}

uint8_t Settings::getAngleOfView() const {
    return angleOfView;
}

bool Settings::isDebug() const {
    return debug;
}

void Settings::setNumberOfAgents(uint8_t numberOfAgents) {
    Settings::numberOfAgents = numberOfAgents;
}

void Settings::setRangeOfView(uint16_t rangeOfView) {
    Settings::rangeOfView = rangeOfView;
}

void Settings::setAngleOfView(uint8_t angleOfView) {
    Settings::angleOfView = angleOfView;
}

void Settings::setDebug(bool debug) {
    Settings::debug = debug;
}

uint8_t Settings::getMapNumber() const {
    return mapNumber;
}

uint8_t Settings::getMinNumberOfAgents() const {
    return minNumberOfAgents;
}

uint8_t Settings::getMaxNumberOfAgents() const {
    return maxNumberOfAgents;
}

uint16_t Settings::getMinRangeOfView() const {
    return minRangeOfView;
}

uint16_t Settings::getMaxRangeOfView() const {
    return maxRangeOfView;
}

uint8_t Settings::getMinAngleOfView() const {
    return minAngleOfView;
}

uint8_t Settings::getMaxAngleOfView() const {
    return maxAngleOfView;
}

uint8_t Settings::getMinManNumber() const {
    return minManNumber;
}

uint8_t Settings::getMaxManNumber() const {
    return maxManNumber;
}