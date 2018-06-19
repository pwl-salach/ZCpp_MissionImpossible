//
// Created by salach on 3/1/18.
//

/*!
 * @file Headquarters.h
 * @brief Deklaracja klasy Headquarters
 */

#ifndef ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
#define ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H

#include "Point.h"
#include "Agent.h"
#include "Environment.h"

/*!
 * @brief Obiekt tej klasy zarządza poszukiwaniami
 */
class Headquarters {
public:
    /*!
     * @brief Wykorzystywany konstruktor
     * @param agents wskaźnik do wektora ze wskaźnikami do agentów
     * @param environment wskaźnik do obiektu środowiska
     */
    Headquarters(std::vector<Agent *> *agents, Environment *environment);

    /*!
     * @brief Rozsyła informację o położeniu gracza do wszystkich agentów
     */
    void broadcastPlayerPosition();

    /*!
     * @brief Iteruje po wszystkich agentach wydając im pozkazy odnośnie przeszukiwań
     */
    void planSearching();

    /*!
     * @brief Wybiera punk do sprawdzenia dla danego agenta
     * @param agent rozważany agent
     */
    void planSearching(Agent *agent);

    /*!
     * @brief Przyjmuje zgloszenie o znalezeniu gracza od jednego z agentów i przekazuje je do pozostałych
     * @param position pozycja gracza
     */
    void acceptThePositionReport(Point &position);

private:
    bool isPlayerSeen();

    bool checkedAlready(Point point, float threshold);

    std::vector<Agent *> *agents;
    Point playerPosition;
    Point lastPlayerPosition;
    Environment *environment;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_HEADQUARTERS_H
