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

class Headquarters {
public:
    void broadcastPlayerPosition();
    void planSearching();
    void sendOrder(Point locationToCheck, Agent *agent);

    std::vector<Agent*>* getAgents() const;

private:
    std::vector<Agent*> *agents;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
