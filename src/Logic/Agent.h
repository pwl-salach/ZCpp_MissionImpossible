//
// Created by salach on 3/1/18.
//
/*!
 * @file Agent.h
 * @brief Deklaracja klasy Agent
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
#define ZCPP_MISSIONIMPOSSIBLE_AGENTS_H


#include <stack>
#include "Person.h"
#include "Point.h"
#include "Scanner.h"
#include "Obstacle.h"

/*!
 * @brief Forward declaration klasy Headquarters
 * \see Headquarters.h
 */
class Headquarters;

/*!
 * @brief Obiekty tej klasy mają za zadanie znaleźć i złapać gracza.
 */
class Agent : public Person, public Obstacle {
public:
    /*!
     * @brief Wykorzystywany konstruktor
     * @param rangeOfView aasięg widzenia agenta
     * @param angleOfView kąt widzenia agenta
     */
    Agent(uint16_t rangeOfView, uint8_t angleOfView);

    /*!
     * @brief Metoda aktualizująca pozycję agenta na wskazaną
     * @param newPosition docelowa pozycja agenta
     */
    void updatePlayerPosition(const Point &newPosition);

    /*!
     * @brief Aktualizuje cel poszukiwań na rządanie obiektu klasy Headquarters. Docelowa kolejka zostaje wyczyszczona.
     * @param destination nowy cel poszukiwań
     */
    void updateOrders(const Point &destination);

    /*!
     * @brief Wylicza nową pozycję na podstawie podanej rotacji w przestrzeni. Uwzględnia zmieniącą się prędkość agenta.
     * @param rot podana rotacja
     * @return nowa pozycja jaką osiągnąłby agent przy danej rotacji
     */
    Point calculateNewPosition(uint16_t rot) override;

    /*!
     * @brief Metoda wywoływana w każdej pętli logiki gry. Odpowiada za działanie agenta.
     */
    void update();

    /*!
     * @brief Sprawdza czy lista lokacji do sprawdzenia przez tego agenta jest pusta.
     * @return
     */
    bool isPathStackEmpty();

    /*!
     * @brief Metoda reprezentuje próbę złapania gracza przez danego agenta.
     * @param player wskaźnik na obiekt gracza
     * @return status powodzenia operacji
     */
    bool catchPlayer(Player *player);

    /*!
     * @brief Setter wskaźnika na pole headquarters. Agent musi mieć możliwość odwołania się do swoich "przełożonych"
     * @param headquarters wskaźnik na obiekt klasy Headquarters
     */
    void setHeadquarters(Headquarters *headquarters);

    /*!
     * @brief Metoda odpowiadająca za wykrywanie przeszkód i w razie potrzeby wywołanie wyznaczannia trasy alternatywnej.
     * @param environment wskaźnik na obiekt reprezentujący środowisko
     */
    void lookAround(const Environment *environment);

    /*!
     * @brief Metoda zmienia kierynek poszuczania się agenta tak, aby oddalić się od wskazanej przeszkody.
     * @param obstacle przeszkoda od której agent ma się oddalić
     * \bug metoda nie sprawdza kolizji przed zmianą pozycji
     */
    void moveAwayFrom(Obstacle *obstacle);

    /*!
     * @return zwraca status widoczności gracza przez agenta
     */
    bool seesPlayer() const;

    /*!
     * @brief Pobiera kolejny punkt do którego agent ma się udać
     * @return kolejny punkt docelowy
     */
    Point getNextDestination();

    /*!
     * \breif Getter obiektu klasy Scanner
     * @return obiekt klasy Scanner zwracany przez referencję
     */
    const Scanner &getScanner() const;

    /*!
     * @brief Getter aktualnie omijanego punktu przeszkody.
     * @return punkt z obwodu przeszkody zwracany przez referencję
     */
    const Point &getPassingPoint() const;

private:
    void findOtherWay(const Environment *environment, std::vector<Point> obstacle);

    void updateTheWayAround(const Point &newPassingPoint);

    double getAlpha(float xDistance, float yDistance) const;

    void reportPlayerPosition(Point &position);

    Scanner scanner;
    std::stack<Point> pathStack;
    Headquarters *headquarters;
    bool visiblePlayer;
    Point passingPoint;
    float speed;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_AGENTS_H
