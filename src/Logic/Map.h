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
    Map();
    Map(Player *pPlayer, uint8_t mapFileId);

    virtual ~Map();

    uint16_t getSizeX() const;

    uint16_t getSizeY() const;

    const std::vector<Obstacle*> &getObstacles();

    bool isPointInsideRectangle(const std::vector<Point> &rectVertices, const Point &point);
    bool overlappingRectangles(const std::vector<Point> &firstRectVertices,
                               const std::vector<Point> &secondRectVertices);
    bool checkCollisions(Person *person);

    bool checkVictoryCondition();

private:
    std::vector<Obstacle*> obstacles;
    std::vector<Agent*> *agents;
    Player *player;
    uint16_t sizeX;
    uint16_t sizeY;
    Point finishPoint;
    uint8_t finishPointRadius;

    void loadSizeFromFileContent(const std::string &configString);
    void loadPlayerStartingPosition(const std::string &configString);
    void loadAgentsPositions(const std::string &configString);
    void loadFinishPoint(const std::string& configString);
    void createFence();

    template <class T> void loadObstaclesFromFileContent(std::string &configString){
        std::vector<std::string> parts = Dictionary::splitString(configString, ':');
        std::vector<std::string> obstacleSize = Dictionary::splitString(parts.at(0), 'x');
        auto obstacleSizeX = uint16_t(std::atoi(obstacleSize.at(0).c_str()));
        auto obstacleSizeY = uint16_t(std::atoi(obstacleSize.at(1).c_str()));
        std::vector<std::string> obstacleCords = Dictionary::splitString(parts.at(1), ';');
        for(auto info : obstacleCords){
            std::vector<std::string> params = Dictionary::splitString(info, ',');
            auto x = uint16_t(std::atoi(params.at(0).c_str()));
            auto y = uint16_t(std::atoi(params.at(1).c_str()));
            auto r = uint16_t(std::atoi(params.at(2).c_str()));
            T* obstacle = new T(Point(x, y),obstacleSizeX, obstacleSizeY, r);
            this->obstacles.push_back(obstacle);
        }
    }

    bool areClose(PhysicalObject *firstObject, PhysicalObject *secondObject);

    bool objectOutsideBoundaries(PhysicalObject *object);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_MAP_H
