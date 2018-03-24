//
// Created by salach on 3/1/18.
//

#include <map>
#include <cmath>
#include "../Utils/FileManager.h"
#include "Map.h"
#include "Lake.h"
#include "Box.h"
#include "Fence.h"

Map::Map(){
};

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
        }else if (Dictionary::stringStartsWith(line, "finish:")){
            Dictionary::cutString(line, "finish:");
            this->loadFinishPoint(line);
        }
    }
    if(!this->finishPoint.isSet()){
        throw "No finish point. This game would be pointless!";
    }
    this->createFence();
}

void Map::loadSizeFromFileContent(const std::string &configString) {
    std::vector<std::string> mapSize = Dictionary::splitString(configString, 'x');
    this->sizeX = uint16_t(std::atoi(mapSize.at(0).c_str()));
    this->sizeY = uint16_t(std::atoi(mapSize.at(1).c_str()));
}

void Map::loadPlayerStartingPosition(const std::string &configString) {
    std::vector<std::string> params = Dictionary::splitString(configString, ',');
    auto x = uint16_t(std::atoi(params.at(0).c_str()));
    auto y = uint16_t(std::atoi(params.at(1).c_str()));
    auto r = uint16_t(std::atoi(params.at(2).c_str()));
    this->player->setPosition(Point(x,y));
    this->player->setRotation(r);
}

void Map::loadFinishPoint(const std::string &configString) {
    std::vector<std::string> params = Dictionary::splitString(configString, ',');
    auto x = uint16_t(std::atoi(params.at(0).c_str()));
    auto y = uint16_t(std::atoi(params.at(1).c_str()));
    auto radius = uint8_t(std::atoi(params.at(2).c_str()));
    if(radius < this->player->getSizeX() * 1.5 && radius < this->player->getSizeY() * 1.5){
        throw "Finish Point radius less then 0";
    }
    this->finishPointRadius = radius;
    if(x < 0 && this->sizeX < x){
        throw "Finish Point X-coordinate out of range!";
    }
    if(y < 0 && this->sizeY < y){
        throw "Finish Point Y-coordinate out of range!";
    }
    if (x != 0 && y != 0 && x != this->sizeX && y != this->sizeY){
        throw "Finish point has to be on the border of the map!";
    }
    this->finishPoint = Point(x,y);
}

void Map::createFence() {
    Fence* topFence = new Fence(Point(this->sizeX/2, 0), this->sizeX, 0);
    Fence* rightFence = new Fence(Point(this->sizeX, this->sizeY/2), this->sizeY, 90);
    Fence* bottomFence = new Fence(Point(this->sizeX/2, this->sizeY), this->sizeX, 0);
    Fence* leftFence = new Fence(Point(0, this->sizeY/2), this->sizeY, 90);
    if (this->finishPoint.getY() == 0 || this->finishPoint.getY() == this->sizeY) {
        if (this->finishPoint.getX() > this->finishPointRadius
            && this->sizeX - this->finishPoint.getX() > this->finishPointRadius) {

            double tempFenceSizeX = this->finishPoint.getX() - this->finishPointRadius;
            Fence*& temp = (this->finishPoint.getY() == 0) ? topFence : bottomFence;
            delete temp;
            temp = new Fence(Point(tempFenceSizeX / 2, this->finishPoint.getY()), static_cast<uint16_t>(tempFenceSizeX), 0);

            tempFenceSizeX = this->sizeX - this->finishPoint.getX() + this->finishPointRadius;
            Fence* tempFence = new Fence(Point(this->finishPoint.getX() + this->finishPointRadius + tempFenceSizeX/2,
                                               this->finishPoint.getY()), static_cast<uint16_t>(tempFenceSizeX), 0);
            this->obstacles.push_back(tempFence);
        }
    }
    this->obstacles.push_back(topFence);
    this->obstacles.push_back(rightFence);
    this->obstacles.push_back(bottomFence);
    this->obstacles.push_back(leftFence);
}

uint16_t Map::getSizeX() const {
    return sizeX;
}

uint16_t Map::getSizeY() const {
    return sizeY;
}

const std::vector<Obstacle*> &Map::getObstacles() {
    return obstacles;
}

bool Map::checkCollisions(Person *person) {
    bool collision = false;
    uint16_t newRot = person->calculateNewRotation();
    Point newPos = person->calculateNewPosition(newRot);
    if(newPos == person->getPosition() && person->getRotation() == newRot){
        return false;
    }
    std::vector<Point>newPersonVertices = person->getCustomVerticesPosition(newPos, newRot);
    std::vector<Point>personVertices = person->getVerticesPosition(); // TODO: only for debug purpose
    for(auto obstacle : this->obstacles){
        if(this->areClose(person, obstacle)){
            collision = overlappingRectangles(obstacle->getVerticesPosition(), newPersonVertices);
            if (collision)
                return collision;
        }
    }
    return collision;
}

bool Map::areClose(PhysicalObject *firstObject, PhysicalObject *secondObject) {
    auto minDistance = firstObject->getDiagonalLength()/2 + secondObject->getDiagonalLength()/2;
    auto xDistance = abs(firstObject->getPosition().getX() - secondObject->getPosition().getX());
    auto yDistance = abs(firstObject->getPosition().getY() - secondObject->getPosition().getY());
    return xDistance <= minDistance && yDistance <= minDistance;
}

bool Map::isPointInsideRectangle(const std::vector<Point> &rectVertices, const Point &point) {
    int counter = 0;
    double xMin = rectVertices.at(0).getX();
    double yMin = rectVertices.at(0).getY();
    double xMax =0, yMax = 0;
    for(uint8_t i=0; i<rectVertices.size(); i++){
        uint8_t nextIndex = (i+1 < rectVertices.size()) ? i+1 : 0;
        Point currPoint = rectVertices.at(i);
        if (currPoint.getX() < xMin)
            xMin = currPoint.getX();
        if (currPoint.getX() > xMax)
            xMax = currPoint.getX();
        if (currPoint.getY() < yMin)
            yMin = currPoint.getY();
        if (currPoint.getY() > yMax)
            yMax = currPoint.getY();
        Point nextPoint = rectVertices.at(nextIndex);
        if (currPoint.sameXCoordinate(nextPoint)){
            continue;
        }
        auto calcY = (point.getX()-currPoint.getX())*(currPoint.getY() - nextPoint.getY())/(currPoint.getX() - nextPoint.getX()) + currPoint.getY();
        if(calcY > point.getY()){
            counter++;
        } else if(calcY < point.getY()){
            counter--;
        } else {
            return true;
        }
    }
    if (point.getX() >= xMin && point.getX() <= xMax && point.getY() >= yMin && point.getY() <= yMax )
        return counter == 0;
    else
        return false;
}

bool
Map::overlappingRectangles(const std::vector<Point> &firstRectVertices, const std::vector<Point> &secondRectVertices) {
    bool overlapping;
    for(const auto &vertex : firstRectVertices){
        overlapping = this->isPointInsideRectangle(secondRectVertices, vertex);
        if (overlapping){
            return true;
        }
    }
    for(const auto &vertex : secondRectVertices){
        overlapping = this->isPointInsideRectangle(firstRectVertices, vertex);
        if (overlapping){
            return true;
        }
    }
    return false;
}

Map::~Map() {
    for(auto it: this->obstacles){
        delete it;
     }
    this->obstacles.clear();
}

bool Map::checkVictoryCondition() {
    bool playerOutside = this->objectOutsideBoundaries(this->player);
    bool closeToExitPoint = this->player->getPosition().closeTo(this->finishPoint, this->finishPointRadius);
    return  playerOutside && closeToExitPoint;
}

bool Map::objectOutsideBoundaries(PhysicalObject *object) {
    auto x = object->getPosition().getX();
    auto y = object->getPosition().getY();
    return 0 > x || x > this->sizeX || 0 > y || y > this->sizeY;
}
