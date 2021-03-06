//
// Created by salach on 2/28/18.
//

#include "Settings.h"

Settings::Settings() {
    mapNumber = 2;
    numberOfAgents = 3;
    rangeOfView = 120;
    angleOfView = 60;
    debug = false;

    minMapNumber = 1;
    maxMapNumber = 2;
    minNumberOfAgents = 1;
    maxNumberOfAgents = 5;
    minRangeOfView = 50;
    maxRangeOfView = 200;
    minAngleOfView = 20;
    maxAngleOfView = 90;
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

uint8_t Settings::getEnvironmentNumber() const {
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
    return minMapNumber;
}

uint8_t Settings::getMaxManNumber() const {
    return maxMapNumber;
}
