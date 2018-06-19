//
// Created by Salach on 25.03.2018.
//
/*!
 * @file SampledLine.h
 * @brief Deklaracja klasy SampledLine
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H
#define ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H


#include <vector>
#include "Point.h"
#include "Line.h"

/*!
 * @brief Klasa dziedzicząca po klasie Line, mająca podobne przeznaczenie, wykorzystywana do szczełolnych zastosowań.
 * Reprezentuje spróbkowany odcinek.
 */
class SampledLine : public Line {
public:
    /*!
     * @brief Wykorzystywany konstruktor. Wyznacza współczynniki linii oraz równoodległe punktu na niej.
     * @param beginning punk początkowy odcinka
     * @param end punk końcowy odcinka
     * @param samplesCount ilość próbek
     */
    SampledLine(const Point &beginning, const Point &end, uint16_t samplesCount);

    /*!
     * @return wektor ze spróbkowanymi punktami odcinka
     */
    const std::vector<Point> &getSamples() const;

private:
    std::vector<Point> samples;
    float step;
};


#endif //ZCPP_MISSIONIMPOSSIBLE_SAMPLEDLINE_H
