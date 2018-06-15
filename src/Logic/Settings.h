//
// Created by salach on 2/28/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H
#define ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H

#include <cstdint>

class Settings {

public:
    Settings();
    uint8_t getNumberOfAgents() const;

    uint16_t getRangeOfView() const;

    uint8_t getAngleOfView() const;

    bool isDebug() const;

    void setNumberOfAgents(uint8_t numberOfAgents);

    void setRangeOfView(uint16_t rangeOfView);

    void setAngleOfView(uint8_t angleOfView);

    void setDebug(bool debug);

    uint8_t getEnvironmentNumber() const;

    uint8_t getMinNumberOfAgents() const;

    uint8_t getMaxNumberOfAgents() const;

    uint16_t getMinRangeOfView() const;

    uint16_t getMaxRangeOfView() const;

    uint8_t getMinAngleOfView() const;

    uint8_t getMaxAngleOfView() const;

    uint8_t getMinManNumber() const;

    uint8_t getMaxManNumber() const;

private:
    uint8_t environmentNumber;
    uint8_t numberOfAgents;
    uint16_t rangeOfView;
    uint8_t angleOfView;
    bool debug;

    uint8_t minManNumber;
    uint8_t maxManNumber;
    uint8_t minNumberOfAgents;
    uint8_t maxNumberOfAgents;
    uint16_t minRangeOfView;
    uint16_t maxRangeOfView;
    uint8_t minAngleOfView;
    uint8_t maxAngleOfView;
};

#endif //ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H
