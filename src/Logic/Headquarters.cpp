//
// Created by salach on 3/1/18.
//

#include "Headquarters.h"

std::vector<Agent *>* Headquarters::getAgents() const {
    return agents;
}

void Headquarters::planSearching() {
    for(auto agent : *agents) {
        if (agent->emptyPathStack()) {
            auto x = std::rand() % map->getSizeX();
            auto y = std::rand() % map->getSizeY();
            agent->updateOrders(Point(x, y));
        }
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
