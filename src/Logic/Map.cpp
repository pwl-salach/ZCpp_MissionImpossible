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
#include "Line.h"


Map::Map(Player *player, std::vector<Agent *> *agents, uint8_t mapFileID) : player(player), agents(agents){
    std::string fileName = "map_";
    fileName += std::to_string(mapFileID) + ".txt";
    std::string mapConfig = FileManager::readTextFile(fileName);
    std::vector<std::string> configMainParts = Dictionary::splitString(mapConfig, '\n');
    for (auto line : configMainParts){
        if (Dictionary::stringStartsWith(line, "size:")){
            Dictionary::cutString(line, "size:");
            loadSizeFromFileContent(line);
        }else if (Dictionary::stringStartsWith(line, "box:")){
            Dictionary::cutString(line, "box:");
            loadObstaclesFromFileContent<Box>(line);
        }else if (Dictionary::stringStartsWith(line, "lake:")){
            Dictionary::cutString(line, "lake:");
            loadObstaclesFromFileContent<Lake>(line);
        }else if (Dictionary::stringStartsWith(line, "player:")){
            Dictionary::cutString(line, "player:");
            loadPlayerStartingPosition(line);
        }else if (Dictionary::stringStartsWith(line, "agent:")){
            Dictionary::cutString(line, "agent:");
            loadAgentsPositions(line);
        }else if (Dictionary::stringStartsWith(line, "finish:")) {
            Dictionary::cutString(line, "finish:");
            loadFinishPoint(line);
        }
    }
    if(!finishPoint.isSet()){
        throw std::runtime_error( "No finish point. This game would be pointless!");
    }
    createFence();
    for(auto agent : *agents){
        obstacles.push_back(agent);
    }
}

void Map::loadSizeFromFileContent(const std::string &configString) {
    std::vector<std::string> mapSize = Dictionary::splitString(configString, 'x');
    sizeX = uint16_t(std::atoi(mapSize.at(0).c_str()));
    sizeY = uint16_t(std::atoi(mapSize.at(1).c_str()));
}

void Map::loadPlayerStartingPosition(const std::string &configString) {
    std::vector<std::string> params = Dictionary::splitString(configString, ',');
    auto x = std::atoi(params.at(0).c_str());
    auto y = std::atoi(params.at(1).c_str());
    auto r = uint16_t(std::atoi(params.at(2).c_str()));
    checkInitPosition(x, y);
    r = recalculateRotation(r);
    player->setInitialOrientation(Point(x, y), r);
}

void Map::loadAgentsPositions(const std::string &configString) {
    std::vector<std::string> parts = Dictionary::splitString(configString, ';');
    if(agents->size() > parts.size()){
        throw std::runtime_error("Not enough agents initial positions in the config file!");
    }
    uint8_t index = 0;
    for(auto agent : *agents){
        auto info = parts.at(index);
        /// TODO warto byloby ten fragment uogolnic ****
        std::vector<std::string> params = Dictionary::splitString(info, ',');
        auto x = std::atoi(params.at(0).c_str());
        auto y = std::atoi(params.at(1).c_str());
        auto r = uint16_t(std::atoi(params.at(2).c_str()));
        checkInitPosition(x, y);
        r = recalculateRotation(r);
        /// ****
        agent->setInitialOrientation(Point(x, y), r);
        index++;
    }
}

void Map::loadFinishPoint(const std::string &configString) {
    std::vector<std::string> params = Dictionary::splitString(configString, ',');
    auto x = std::atoi(params.at(0).c_str());
    auto y = std::atoi(params.at(1).c_str());
    auto radius = uint8_t(std::atoi(params.at(2).c_str()));
    if(radius < player->getSizeX() * 1.5 && radius < player->getSizeY() * 1.5){
        throw std::runtime_error( "Finish Point radius less then 0");
    }
    finishPointRadius = radius;
    checkInitPosition(x, y);
    if (x != 0 && y != 0 && x != sizeX && y != sizeY){
        throw std::runtime_error( "Finish point has to be on the border of the map!");
    }
    finishPoint = Point(x,y);
}

void Map::createFence() {
    Fence* topFence = new Fence(Point(sizeX/2, 0), sizeX, 0);
    Fence* rightFence = new Fence(Point(sizeX, sizeY/2), sizeY, 90);
    Fence* bottomFence = new Fence(Point(sizeX/2, sizeY), sizeX, 0);
    Fence* leftFence = new Fence(Point(0, sizeY/2), sizeY, 90);
    if (finishPoint.getY() == 0 || finishPoint.getY() == sizeY) {
        if (finishPoint.getX() > finishPointRadius
            && sizeX - finishPoint.getX() > finishPointRadius) {

            float tempFenceSizeX = finishPoint.getX() - finishPointRadius;
            Fence*& temp = (finishPoint.getY() == 0) ? topFence : bottomFence;
            delete temp;
            temp = new Fence(Point(tempFenceSizeX / 2, finishPoint.getY()), static_cast<uint16_t>(tempFenceSizeX), 0);
            tempFenceSizeX = sizeX - finishPoint.getX() + finishPointRadius;
            auto centralPoint = Point(finishPoint.getX() + finishPointRadius + tempFenceSizeX/2, finishPoint.getY());
            auto tempFence = new Fence(centralPoint, static_cast<uint16_t>(tempFenceSizeX), 0);
            obstacles.push_back(tempFence);
        }
    }
    obstacles.push_back(topFence);
    obstacles.push_back(rightFence);
    obstacles.push_back(bottomFence);
    obstacles.push_back(leftFence);
}

uint16_t Map::getSizeX() const {
    return sizeX;
}

uint16_t Map::getSizeY() const {
    return sizeY;
}

const std::vector<Obstacle*> &Map::getObstacles() const{
    return obstacles;
}

PhysicalObject * Map::checkCollisions(Person *person) {
    uint16_t newRot = person->calculateNewRotation();
    Point newPos = person->calculateNewPosition(newRot, person->getMovementSpeed()*3);
    if(newPos == person->getPosition() && person->getRotation() == newRot){
        return nullptr;
    }
    std::vector<Point>newPersonVertices = person->getCustomVerticesPosition(newPos, newRot);
    for(auto obstacle : obstacles){
        if(areClose(person, obstacle)){
            if (overlappingRectangles(obstacle->getVerticesPosition(), newPersonVertices)){
                return obstacle;
            }
        }
    }
    return nullptr;
}

bool Map::areClose(PhysicalObject *firstObject, PhysicalObject *secondObject) {
    //TODO do poprawy
    if(firstObject == secondObject)
        return false;
    auto minDistance = firstObject->getDiagonalLength()/2 + secondObject->getDiagonalLength()/2;
    auto xDistance = abs(firstObject->getPosition().getX() - secondObject->getPosition().getX());
    auto yDistance = abs(firstObject->getPosition().getY() - secondObject->getPosition().getY());
    return xDistance <= minDistance && yDistance <= minDistance;
}

bool Map::areClose(const Point &point, PhysicalObject *object) const{
    auto xDistance = abs(object->getPosition().getX() - point.getX());
    auto yDistance = abs(object->getPosition().getY() - point.getY());
    return object->getSizeX()/2 <= xDistance && object->getSizeY()/2 <= yDistance;
}

bool Map::areClose(const Point &point, const Point &other, float threshold) const{
    bool xClose = std::fabs(point.getX() - other.getX()) < threshold;
    bool yClose = std::fabs(point.getY() - other.getY()) < threshold;
    return xClose && yClose;
}

bool Map::overlappingRectangles(const std::vector<Point> &firstRectVer, const std::vector<Point> &secondRectVer) {
    auto overlaps = [this](const std::vector<Point> &some, const std::vector<Point> &other)->bool{
        for(const auto &vertex : some){
            bool overlapping = isPointInsideRectangle(other, vertex);
            if (overlapping){
                return true;
            }
        }
        return false;
    };
    bool firstOverlappingSecond = overlaps(firstRectVer, secondRectVer);
    bool secondOverlappingFirst = overlaps(secondRectVer, firstRectVer);
    return firstOverlappingSecond || secondOverlappingFirst;
}

bool Map::isPointInsideRectangle(const std::vector<Point> &rectVertices, const Point &point) const{
    int counter = 0;
    float xMin = rectVertices.at(0).getX();
    float yMin = rectVertices.at(0).getY();
    float xMax =0, yMax = 0;
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
        Line line = Line(currPoint, nextPoint);
        auto calcY = line.calculate(point.getX());
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

Map::~Map() {
    for(auto it: obstacles){
       delete it;
    }
    obstacles.clear();
}

bool Map::checkVictoryCondition() {
    bool playerOutside = objectOutsideBoundaries(player);
    bool closeToExitPoint = areClose(player->getPosition(), finishPoint, finishPointRadius);
    return  playerOutside && closeToExitPoint;
}

bool Map::objectOutsideBoundaries(PhysicalObject *object) {
    auto x = object->getPosition().getX();
    auto y = object->getPosition().getY();
    return 0 > x || x > sizeX || 0 > y || y > sizeY;
}

void Map::checkInitPosition(float x, float y) const{
    if(x < 0 && sizeX < x){
        throw std::runtime_error( "X-coordinate out of range!");
    }
    if(y < 0 && sizeY < y){
        throw std::runtime_error( "Y-coordinate out of range!");
    }
}

uint16_t Map::recalculateRotation(uint16_t r) {
    int period = 0;
    if(abs(r) > 360){
        period = (r/360)*360;
        period = (r >=0 ) ? period : -period;
    }
    r = (uint16_t)(r - period);
    return r;
}

bool Map::isPointThePlayerPosition(const Point &point) const{
    if(areClose(point, player->getPosition(), 30)) {
        std::vector<Point> playerVertices = player->getVerticesPosition();
        return isPointInsideRectangle(playerVertices, point);
    }
    return false;
}

bool Map::isPointInsideObstacle(const Point &point, Obstacle *pObstacle) const{
    if(!areClose(point, pObstacle)){
        return isPointInsideRectangle(pObstacle->getVerticesPosition(), point);
    }
    return false;
}

float Map::calculateDistance(const Point &some, const Point &other) const{
    auto xDiff = some.getX() - other.getX();
    auto yDiff = some.getY() - other.getY();
    return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

bool Map::isAccessible(const Point &point) {
    for(auto obstacle: obstacles){
        if(isPointInsideObstacle(point, obstacle)){
            return false;
        }
    }
    return true;
}

