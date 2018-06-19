//
// Created by salach on 3/1/18.
//

/*!
 * @file Scanner.h
 * @brief Deklaracja klasy Scanner
 */

#ifndef ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
#define ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H


#include <cstdint>
#include <vector>
#include "Obstacle.h"

/*!
 * @brief Forward declaration klasy Environment
 * \see Environment.h
 */
class Environment;

/*!
 * @brief Forward declaration klasy Agent
 * \see Agent.h
 */
class Agent;

/*!
 * @brief Obiekty tej klasy przedstawiają spobów w jaki poszczególni agenci widą otoczenie.
 */
class Scanner {
public:
    /*!
     * @brief Wykorzystywany konstruktor
     * @param pRange zasięg widzenia
     * @param pAngle kąt widzenia
     * @param agent wskaźnik do agenta do którego przynależy skaner
     */
    Scanner(uint16_t pRange, uint8_t pAngle, Agent *pAgent);

    /*!
     * @brief Metoda skanująca otoczenie w poszukiwaniu gracza i przeszkód.
     * @param environment wskaźnik do obiektu klasy Environment
     * @param playerPosition punkt przekazywany przez referencję przez którego jest zwracana odnaleziona pozycja gracza
     * @return wektor wektorów punktów, poszczególne wektory punktów należą do oddzialnych przeszkód
     */
    std::vector<std::vector<Point> > search(const Environment *environment, Point &playerPosition);

    /*!
     * @return punktu przeskanowane przez skaner w trakcie danej iteracji
     */
    const std::vector<Point> &getScannedPoints() const;

private:
    Point calculateMaxRangePoint(const Point &beginning, int rotation);

    void recalculateAttachmentPosition(Agent *agent);

    std::vector<Point> scannedPoints;
    Point position;
    uint16_t range;
    uint8_t angle;
    Agent *agent;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FIELDOFVIEW_H
