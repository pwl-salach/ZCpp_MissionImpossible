//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_MAP_H
#define ZCPP_MISSIONIMPOSSIBLE_MAP_H


#include <vector>
#include "Agent.h"
#include "Player.h"
#include "../Utils/Dictionary.h"
#include "PhysicalObject.h"
#include "Obstacle.h"

class Map {
public:
    Map(Player *pPlayer, uint8_t mapFileId);

    uint16_t getSizeX() const;

    uint16_t getSizeY() const;

    const std::vector<Obstacle *> &getObstacles() const;

private:
    std::vector<Obstacle*> obstacles;
    std::vector<Agent*> *agents;
    Player *player;
    uint16_t sizeX;
    uint16_t sizeY;

    void loadSizeFromFileContent(std::basic_string<char> &basic_string);

    template <class T> void loadObstraclesFromFileContent(std::basic_string<char> &basic_string){
        std::vector<std::string> parts = Dictionary::splitString(basic_string, ':');
        std::vector<std::string> boxSize = Dictionary::splitString(parts.at(0), 'x');
        auto boxSizeX = uint16_t(std::atoi(boxSize.at(0).c_str()));
        auto boxSizeY = uint16_t(std::atoi(boxSize.at(1).c_str()));
        std::vector<std::string> boxesCords = Dictionary::splitString(parts.at(1), ';');
        for(auto info : boxesCords){
            std::vector<std::string> params = Dictionary::splitString(info, ',');
            auto x = uint16_t(std::atoi(params.at(0).c_str()));
            auto y = uint16_t(std::atoi(params.at(1).c_str()));
            auto r = uint16_t(std::atoi(params.at(2).c_str()));
            T *box = new T(boxSizeX, boxSizeY, x, y, r);
            this->obstacles.push_back(box);
        }
    }

    void loadPlayerStartingPosition(std::string &basic_string);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_MAP_H
