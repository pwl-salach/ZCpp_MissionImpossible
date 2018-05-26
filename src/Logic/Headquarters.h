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
    void planSearching(Agent *agent);
    std::vector<Agent*>* getAgents() const;
    void acceptThePositionReport(Point &position);

private:
    bool isPlayerSeen();
    std::vector<Agent*> *agents;
    Point playerPosition;
    Point lastPlayerPosition;
    Map* map;

    bool checkedAlready(Point point, float threshold);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
