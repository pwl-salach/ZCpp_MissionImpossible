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
    Map(Player *player, std::vector<Agent *> *agents, uint8_t mapFileID);

    ~Map();

    uint16_t getSizeX() const;

    uint16_t getSizeY() const;

    const std::vector<Obstacle*> &getObstacles() const;

    bool isPointInsideRectangle(const std::vector<Point> &rectVertices, const Point &point) const;
    bool overlappingRectangles(const std::vector<Point> &firstRectVer,
                               const std::vector<Point> &secondRectVer);
    PhysicalObject * checkCollisions(Person *person);
    bool isPointThePlayerPosition(const Point &point) const;

    bool checkVictoryCondition();

    bool isPointInsideObstacle(const Point &point, Obstacle *pObstacle) const;

    float calculateDistance(const Point &some, const Point &other) const;

    bool isAccessible(const Point &point);

    bool areClose(const Point &point, const Point &other, float threshold) const;

    bool blocksTheWay(Agent *agent, std::vector<Point> obstacleOutline)const;

    Point getClosePoint(const Point &point, const std::vector<Point> &outline, float threshold) const;

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
    void checkInitPosition(float x, float y) const;

    template <class T> void loadObstaclesFromFileContent(std::string &configString){
        std::vector<std::string> parts = Dictionary::splitString(configString, ':');
        std::vector<std::string> obstacleSize = Dictionary::splitString(parts.at(0), 'x');
        auto obstacleSizeX = uint16_t(std::atoi(obstacleSize.at(0).c_str()));
        auto obstacleSizeY = uint16_t(std::atoi(obstacleSize.at(1).c_str()));
        std::vector<std::string> obstacleCords = Dictionary::splitString(parts.at(1), ';');
        for(const auto &info : obstacleCords){
            std::vector<std::string> params = Dictionary::splitString(info, ',');
            auto x = std::atoi(params.at(0).c_str());
            auto y = std::atoi(params.at(1).c_str());
            auto r = uint16_t(std::atoi(params.at(2).c_str()));
            checkInitPosition(x, y);
            T* obstacle = new T(Point(x, y),obstacleSizeX, obstacleSizeY, r);
            obstacles.push_back(obstacle);
        }
    }

    bool areClose(PhysicalObject *firstObject, PhysicalObject *secondObject);

    bool objectOutsideBoundaries(PhysicalObject *object);

    uint16_t recalculateRotation(uint16_t r);

    bool areClose(const Point &point, PhysicalObject *object) const;

};


#endif //ZCPP_MISSIONIMPOSSIBLE_MAP_H
