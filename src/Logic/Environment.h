//
// Created by salach on 3/1/18.
//
/*!
 * @file Environment.h
 * @brief Deklaracja klasy Environment
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_environment_H
#define ZCPP_MISSIONIMPOSSIBLE_environment_H


#include <vector>
#include "Agent.h"
#include "Player.h"
#include "../Utils/Dictionary.h"
#include "PhysicalObject.h"
#include "Obstacle.h"

/*!
 * @brief Klasa reprezentująca przestrzeń w jakiej przemieszczają się wszystkie fizyczne obiekty w grze.
 */
class Environment {
public:
    /*!
     * @brief Wykorzystywany konstruktor.
     * @param player wskaźnik na obiekt gracza
     * @param agents wskaźnik na wektor agentów
     * @param environmentFileID indeks pliku z konfiguracją mapy gry
     */
    Environment(Player *player, std::vector<Agent *> *agents, uint8_t environmentFileID);

    /*!
     * @brief Domyślny dekonstruktor
     */
    ~Environment();

    /*!
     * @brief Sprawdza czy podany punkt znajduje się wewnątrz prostokątnego obszaru
     * @param rectVertices wierzchołki osprawdzanego obszaru
     * @param point sprawdzany punkt
     * @return prawdę jeżeli punkt jest wewnątrz wskazanego obszaru, w przeciwnym wypadku fałsz
     */
    bool isPointInsideRectangle(const std::vector<Point> &rectVertices, const Point &point) const;

    /*!
     * @brief Sprawdza czy podany punkt znajduje się wewnątrz wskazanej przeszkody
     * @param point sprawdzany punkt
     * @param obstacle sprawdzana przeszkoda
     * @return prawdę jeżeli punkt jest wewnątrz wskazanej przeszkody, w przeciwnym wypadku fałsz
     */
    bool isPointInsideObstacle(const Point &point, Obstacle *obstacle) const;

    /*!
     * @brief Sprawdza czy podane wielokąty nachodzą na siebie
     * @param firstRectVer wierzchołki pierwszego wieloboku
     * @param secondRectVer wierzchołki drugiego wieloboku
     * @return wynik sprawdzenia czy wielokąty posiadają punkty wspólne
     */
    bool overlappingRectangles(const std::vector<Point> &firstRectVer,
                               const std::vector<Point> &secondRectVer);

    /*!
     * @brief Sprawdza przewidywaną kolizję osoby przy jej aktualnym ruchu
     * @param person wskaźnik na obiekty klasy Person
     * @return wskaźnik na kolidujący obiekt
     */
    Obstacle* checkCollisions(Person *person);

    /*!
     * @brief Sprawdza czy w podanym punkcje znajduje się gracz
     * @param point sprawdzany punkt
     * @return status sprawdzenia przynależności punktu do obwodu postaci gracza
     */
    bool isPointThePlayerPosition(const Point &point) const;

    /*!
     * @brief Sprawdza warunek pozytywnego zakończenia rozgrywki
     * @return status sprawdzenia odległości gracza od punktu końcowego
     */
    bool checkVictoryCondition();

    /*!
     * @brief Oblicza odległość między dwoma punktami
     * @param some pierwszy punkt przekazany przez referencję
     * @param other drugi punkt przekazany przez referencję
     * @return odległość między punktami
     */
    float calculateDistance(const Point &some, const Point &other) const;

    /*!
     * @brief Sprawdza czy jest osiągalny do dojścia do niego
     * @param point sprawdzany punk
     * @return status sprawdzenia czy dany punkt nie znajduje się wewnątrz żadnej przeszkody
     */
    bool isAccessible(const Point &point) const;

    /*!
     * @brief Sprawdza czy dwa punkty znajdują się blisko siebie
     * @param point pierwszy punkt przekazany przez referencję
     * @param other drugi punkt przekazany przez referencję
     * @param threshold próg odniesienia
     * @return prawdę jeżeli rożnice obu współrzędnych są mniejsza niż podana wartość
     */
    bool areClose(const Point &point, const Point &other, float threshold) const;

    /*!
     * @brief Wybiera z grupy punktów jeden spełniający warunek na odległość
     * @param point sprawdzany punkt odniesienia
     * @param outline wektor z punktami do sprawdzenia
     * @param threshold próg odniesienia
     * @return zwraca punkt spełniający warunek bliskości lub niezainicjowany punkt
     */
    Point getClosePoint(const Point &point, const std::vector<Point> &outline, float threshold) const;

    /*!
     * @brief Sprawdza czy podana chmura punktw blokuje przejście agentowi
     * @param agent sprawdzany agent
     * @param obstacleOutline wektor zawierający frag,emt obwodu przeszkody
     * @return prawdę jeżeli przynajmniej jeden z punktów znajduje się na bezpośredniej drodze między agentem a jego celem
     */
    bool blocksTheWay(Agent *agent, const std::vector<Point> &obstacleOutline) const;

    /*!
     * @brief Usuwa wektor przeszkód
     */
    void clearObstacles();

    /*!
     * @return wektor ze wskaźnikami na przeszkody
     */
    const std::vector<Obstacle *> &getObstacles() const;

    /*!
     * @return rozmiar otoczenia w zdłuż osi X
     */
    uint16_t getSizeX() const;

    /*!
    * @return rozmiar otoczenia w zdłuż osi Y
    */
    uint16_t getSizeY() const;

private:
    void loadSizeFromFileContent(const std::string &configString);

    void loadPlayerStartingPosition(const std::string &configString);

    void loadAgentsPositions(const std::string &configString);

    void loadFinishPoint(const std::string &configString);

    void createFence();

    void checkInitPosition(float x, float y) const;

    template<class T>
    void loadObstaclesFromFileContent(std::string &configString) {
        std::vector<std::string> parts = Dictionary::splitString(configString, ':');
        std::vector<std::string> obstacleSize = Dictionary::splitString(parts.at(0), 'x');
        auto obstacleSizeX = uint16_t(std::atoi(obstacleSize.at(0).c_str()));
        auto obstacleSizeY = uint16_t(std::atoi(obstacleSize.at(1).c_str()));
        std::vector<std::string> obstacleCords = Dictionary::splitString(parts.at(1), ';');
        for (const auto &info : obstacleCords) {
            std::vector<std::string> params = Dictionary::splitString(info, ',');
            auto x = std::atoi(params.at(0).c_str());
            auto y = std::atoi(params.at(1).c_str());
            auto r = uint16_t(std::atoi(params.at(2).c_str()));
            checkInitPosition(x, y);
            T *obstacle = new T(Point(x, y), obstacleSizeX, obstacleSizeY, r);
            obstacles.push_back(obstacle);
        }
    }

    bool areClose(PhysicalObject *firstObject, PhysicalObject *secondObject);

    bool areClose(const Point &point, PhysicalObject *object) const;

    bool objectOutsideBoundaries(PhysicalObject *object);

    uint16_t recalculateRotation(uint16_t r);

    std::vector<Obstacle *> obstacles;
    std::vector<Agent *> *agents;
    Player *player;
    uint16_t sizeX;
    uint16_t sizeY;
    Point finishPoint;
    uint8_t finishPointRadius;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_environment_H
