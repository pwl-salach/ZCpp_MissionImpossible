//
// Created by Salach on 19.02.2018.
//

/*!
 * @file Game.h
 * @brief Deklaracja klasy Game
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_GAME_H
#define ZCPP_MISSIONIMPOSSIBLE_GAME_H

#include <thread>
#include "../GUI/StartWindow.h"
#include "Environment.h"
#include "Headquarters.h"

/*!
 * @brief Głowna klasa w grze zarządzająca całą jej logiką
 */
class Game {

public:
    /*!
     * @brief Enum określający stan rozgrywki
     */
    enum State {
        RUNNING = 0,  /*!< gra w trakcie */
        PAUSE = 1,    /*!< gra wstrzymana */
        VICTORY = 3,  /*!< gra zakonczona zwycięstwem*/
        LOSE = 4      /*!< gra zakonczona porażką*/
    };

    /*!
     * @brief Wykorzystywany konstruktor
     * @param pSettings ustawienia rozgrywki
     * @param pAgents wektor ze wskaźnikami na agentów
     */
    Game(Settings *pSettings, std::vector<Agent *> pAgents);

    /*!
     * @brief Rozpoczyna rozgrywkę, tworząc wątek i rozpoczynając planowanie poszukiwań
     */
    void start();

    /*!
     * @brief Ponownie startuje wątek z logiką rozgrywki
     */
    void resume();

    /*!
     * @brief Pętla z logiką rozgrywki
     */
    void loop();

    /*!
     * @brief Metoda w której odbywa się aktualizacja stanów wszystkich obiektów
     */
    void update();

    /*!
     * @brief Zakończenie rozgrywki wraz z usunięciem wskaźników do obiektów zarządzanych przez ten obiekt
     */
    void quit();

    /*!
     * @brief Wstrzymuje główny wątek
     */
    void pause();

    /*!
     * @return status rozgrywki
     */
    State getState() const;

    /*!
     * @return referencja do obiektu gracza
     */
    Player &getPlayer();

    /*!
     * @return referencja do obiektu środowiska
     */
    Environment &getEnvironment();

    /*!
    * @return referencja do obiektu ustawień
    */
    Settings *getSettings() const;

    /*!
    * @return referencja do wektora wskźników do graczy
    */
    const std::vector<Agent *> &getAgents() const;

private:
    State state;
    Player player;
    Settings *settings;
    std::vector<Agent *> agents;
    Environment environment;
    Headquarters headquarters;
    std::thread updateLoop;
    uint8_t updatesPerSecond;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_GAME_H
