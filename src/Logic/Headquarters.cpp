//
// Created by salach on 3/1/18.
//

#include "Headquarters.h"
#include <random>

std::vector<Agent *>* Headquarters::getAgents() const {
    return agents;
}

void Headquarters::planSearching() {
    for(auto agent : *agents) {
        if (agent->isPathStackEmpty()) {
            planSearching(agent);
        }
    }
}

void Headquarters::planSearching(Agent *agent) {
    if (isPlayerSeen()) {
        agent->updateOrders(playerPosition);
    } else {
        Point point;
        std::random_device rd;
        std::mt19937 mt(rd());
        if (lastPlayerPosition.isSet()) {
            std::uniform_int_distribution<uint32_t> range(20, 150);
            do {
                for (uint8_t i = 0; i < 5; i++) {
                    auto x = lastPlayerPosition.getX() + range(mt);
                    auto y = lastPlayerPosition.getY() + range(mt);
                    point = Point(x, y);
                    float threshold = 80;
                    if (!checkedAlready(point, threshold)) {
                        break;
                    }
                }
            } while (!map->isAccessible(point));

        } else {
            std::uniform_int_distribution<uint32_t> xRange(0, map->getSizeX());
            std::uniform_int_distribution<uint32_t> yRange(0, map->getSizeY());
            do {
                auto x = xRange(mt);
                auto y = yRange(mt);
                point = Point(x, y);
            } while (!map->isAccessible(point));
        }
        agent->updateOrders(point);
    }
}

void Headquarters::acceptThePositionReport(Point &position) {
    playerPosition = position;
    broadcastPlayerPosition();
    planSearching();
}

void Headquarters::broadcastPlayerPosition() {
    for(auto agent : *agents){
        agent->updatePlayerPosition(playerPosition);
    }
}

Headquarters::Headquarters(std::vector<Agent *> *agents, Map *map) : agents(agents), map(map) {
    for(auto agent : *agents){
        agent->setHeadquarters(this);
    }
}

bool Headquarters::isPlayerSeen() {
    for (auto agent: *agents){
        if(agent->seesPlayer()){
            return true;
        }
    }
    lastPlayerPosition = playerPosition;
    playerPosition = Point();
    return false;
}

bool Headquarters::checkedAlready(Point point, float threshold) {
    for(auto agent: *agents){
        auto pointAgentPosDist = map->calculateDistance(point, agent->getPosition());
        bool checked = pointAgentPosDist <= threshold;
        if (!agent->isPathStackEmpty()){
            auto pointAgentDestDist = map->calculateDistance(point, agent->getNextDestination());
            checked = checked || pointAgentDestDist <= threshold;
        }
        if(checked){
            return  true;
        }
    }
    return false;
}

