//
// Created by salach on 3/1/18.
//

/*!
 * \file
 * \brief Declaration of the Headquarters class
 */

#ifndef ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
#define ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H


#include "Point.h"
#include "Agent.h"
#include "Map.h"

class Headquarters {
public:
    Headquarters(std::vector<Agent *> *agents, Map *map);

    void broadcastPlayerPosition();
    void planSearching();
    void sendOrder(Point locationToCheck, Agent *agent);

    std::vector<Agent*>* getAgents() const;

    void acceptThePositionReport(Point &position);

private:
    std::vector<Agent*> *agents;
    Point playerPosition;
    Map* map;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
