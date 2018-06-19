//
// Created by salach on 3/1/18.
//

/*!
 * @file Person.h
 * @brief Deklaracja klasy Person
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_PERSON_H
#define ZCPP_MISSIONIMPOSSIBLE_PERSON_H


#include <cstdint>
#include "PhysicalObject.h"
#include "Point.h"

/*!
 * @brief Abstrakcyjna klasa uogólniająca obiekty reprezentujące osoby w grze
 */
class Person : virtual public PhysicalObject {
public:
    /*!
     * @brief Enum określający jaki ruch wykonuje obiekt
     */
    enum Movement {
        NONE = 0,       /*!< brak ruchu*/
        FORWARD = 1,    /*!< kroczenie w przód*/
        BACK = 2,       /*!< kroczenie w tył*/
        TURN_LEFT = 3,  /*!< skręcanie w lewo*/
        TURN_RIGHT = 4  /*!< skręcanie w prawo*/
    };

    /*!
     * @brief WYkorzystywany konstruktor. Określa rozmiar i wstępny brak ruchu.
     */
    Person();

    /*!
     * @brief Domyślny dekonstruktor.
     */
    ~Person() override;

    /*!
     * @brief Wylicza nową pozycję na podstawie podanej rotacji w przestrzeni.
     * @param rot podana rotacja
     * @param speed podana prędkość ruchu
     * @return nowa pozycja jaką osiągnąłby obiekt przy danej rotacji i szybkości
     */
    Point calculateNewPosition(uint16_t rot, float speed);

    /*!
     * @brief Wylicza nową pozycję na podstawie podanej rotacji w przestrzeni. Przy ruchu w tył prędkość jest zmniejszana o połowę.
     * @param rot podana rotacja
     * @return nowa pozycja jaką osiągnąłby obiekt przy danej rotacji
     */
    virtual Point calculateNewPosition(uint16_t rot);

    /*!
     * @brief Oblicza nową wartość rotacji uwzględniając nieciągłość przy kącie 360 stopni
     * @return obliczona wartość rotacji
     */
    uint16_t calculateNewRotation();

    /*!
     * @brief Zmienia położenie obiektu
     */
    void move();

    /*!
     * @return maksymalną prędkość poruszania się
     */
    uint8_t getMovementSpeed() const;

    /*!
     * @brief Ustawia ruch liniowy na podany
     * @param movement nowa wartość
     */
    void setMovement(Movement movement);

    /*!
     * @brief Ustawia ruch obrotowy na podany
     * @param movement nowa wartość
     */
    void setTurning(Movement turning);

protected:
    /*!
     * @brief Wylicza nową pozycję na podstawie podanej rotacji w przestrzeni. Biorąc za prędkość i kąt wartości pól klasy.
     * @return nowa pozycja jaką osiągnąłby agent
     */
    Point calculateNewPosition();

    Movement movement;          /*!< określa ruch liniowy */
    Movement turning;           /*!< określa ruch obrotowy */
    uint8_t movementSpeed;      /*!< określa prędkość liniową */
    uint8_t turningSpeed;       /*!< określa prędkość obrotową*/
};


#endif //ZCPP_MISSIONIMPOSSIBLE_PERSON_H
