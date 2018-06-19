//
// Created by salach on 2/28/18.
//
/*!
 * @file Settings.h
 * @brief Deklaracja klasy Settings
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H
#define ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H

#include <cstdint>

/*!
 * @brief Obiekt tej klasy zawiera ustawienia rozgrywki takie jak ilość agentów, parametry ich skanerów, wybór mapy i opcje debugowe
 * Zawiera gettery i settery do wszystkich ustawień, oraz gettery do ich skrajnych wartości.
 */
class Settings {
public:
    Settings();

    /*!
     * @return wartość opcji ilości agentów
     */
    uint8_t getNumberOfAgents() const;

    /*!
     * @return wartość opcji zasięgu widzenia agentów
     */
    uint16_t getRangeOfView() const;

    /*!
     * @return wartość opcji kąta widzenia agentów
     */
    uint8_t getAngleOfView() const;

    /*!
     * @return numer wybranej mapy
     */
    uint8_t getEnvironmentNumber() const;

    /*!
     * @return status włączenia opcji debuggowej
     */
    bool isDebug() const;

    /*!
     * @brief Ustawia wartość opcji numberOfAgents
     * @param numberOfAgents nowa wartość
     */
    void setNumberOfAgents(uint8_t numberOfAgents);

    /*!
     * @brief Ustawia wartość opcji rangeOfView
     * @param rangeOfView nowa wartość
     */
    void setRangeOfView(uint16_t rangeOfView);

    /*!
     * @brief Ustawia wartość opcji angleOfView
     * @param angleOfView nowa wartość
     */
    void setAngleOfView(uint8_t angleOfView);

    /*!
     * @brief Ustawia wartość opcji debug
     * @param debug nowa wartość
     */
    void setDebug(bool debug);

    /*!
     * @return minimalną wartość liczby agentów
     */
    uint8_t getMinNumberOfAgents() const;

    /*!
     * @return maksymalną wartość liczby agentów
     */
    uint8_t getMaxNumberOfAgents() const;

    /*!
     * @return minimalną wartość zasięgu widzenia agentów
     */
    uint16_t getMinRangeOfView() const;

    /*!
     * @return maksymalną wartość zasięgu widzenia agentów
     */
    uint16_t getMaxRangeOfView() const;

    /*!
     * @return minimalną wartość kąta widzenia agentów
     */
    uint8_t getMinAngleOfView() const;

    /*!
     * @return maksymalną wartość kąta widzenia agentów
     */
    uint8_t getMaxAngleOfView() const;

    /*!
     * @return minimalną numer mapy
     */
    uint8_t getMinManNumber() const;

    /*!
     * @return maksymalną numer mapy
     */
    uint8_t getMaxManNumber() const;

private:
    uint8_t mapNumber;
    uint8_t numberOfAgents;
    uint16_t rangeOfView;
    uint8_t angleOfView;
    bool debug;
    uint8_t minMapNumber;
    uint8_t maxMapNumber;
    uint8_t minNumberOfAgents;
    uint8_t maxNumberOfAgents;
    uint16_t minRangeOfView;
    uint16_t maxRangeOfView;
    uint8_t minAngleOfView;
    uint8_t maxAngleOfView;
};

#endif //ZCPP_MISSIONIMPOSSIBLE_SETTINGS_H
