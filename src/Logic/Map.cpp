//
// Created by salach on 3/1/18.
//

#include <map>
#include "Map.h"
#include "../Utils/FileManager.h"
#include "Lake.h"
#include "Box.h"

Map::Map(Player *pPlayer, uint8_t mapFileId) {
    this->player = pPlayer;
    std::string fileName = "map_";
    fileName += std::to_string(mapFileId) + ".txt";
    std::string mapConfig = FileManager::readTextFile(fileName);
    std::vector<std::string> configMainParts = Dictionary::splitString(mapConfig, '\n');
    for (auto line : configMainParts){
        if (Dictionary::stringStartsWith(line, "size:")){
            Dictionary::cutString(line, "size:");
            this->loadSizeFromFileContent(line);
        }else if (Dictionary::stringStartsWith(line, "box:")){
            Dictionary::cutString(line, "box:");
            this->loadObstaclesFromFileContent<Box>(line);
        }else if (Dictionary::stringStartsWith(line, "lake:")){
            Dictionary::cutString(line, "lake:");
            this->loadObstaclesFromFileContent<Lake>(line);
        }else if (Dictionary::stringStartsWith(line, "player:")){
            Dictionary::cutString(line, "player:");
            this->loadPlayerStartingPosition(line);
        }
    }
}

void Map::loadSizeFromFileContent(const std::string &basic_string) {
    std::vector<std::string> mapSize = Dictionary::splitString(basic_string, 'x');
    this->sizeX = uint16_t(std::atoi(mapSize.at(0).c_str()));
    this->sizeY = uint16_t(std::atoi(mapSize.at(1).c_str()));
}

void Map::loadPlayerStartingPosition(const std::string &basic_string) {
    std::vector<std::string> params = Dictionary::splitString(basic_string, ',');
    auto x = uint16_t(std::atoi(params.at(0).c_str()));
    auto y = uint16_t(std::atoi(params.at(1).c_str()));
    auto r = uint16_t(std::atoi(params.at(2).c_str()));
    this->player->setPosition(Point(x,y));
    this->player->setRotation(r);
}

uint16_t Map::getSizeX() const {
    return sizeX;
}

uint16_t Map::getSizeY() const {
    return sizeY;
}

const std::vector<Obstacle *> &Map::getObstacles() {
    return obstacles;
}

Map::Map() {

}
