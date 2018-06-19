//
// Created by salach on 3/1/18.
//

/*!
 * @file FileManager.h
 * @brief Deklaracja klasy FileManager
 */
#ifndef ZCPP_MISSIONIMPOSSIBLE_FILEMANAGER_H
#define ZCPP_MISSIONIMPOSSIBLE_FILEMANAGER_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include <cstring>

/*!
 * @brief Klasa zawierająca same metody statyczne związane z operacjami na plikach.
 */
class FileManager {
public:
    /*!
     * @brief Metoda do wczytywania czcionek z folderu resources.
     * @param fileName nazwa pliku
     * @param size rozmiar czcionki
     * @return wskaźnik do obiektu klasy TTF_Font
     */
    static TTF_Font *loadFont(const std::string &fileName, uint8_t size);

    /*!
     * @brief Metoda do wczytywania obrazów z folderu resources.
     * @param fileName nazwa pliku
     * @return wskaźnik do obiektu klasy SDL_Surface
     */
    static SDL_Surface *loadImage(const std::string &fileName);

    /*!
     * @brief Metoda do odczytywania zawartości pliku tekstowego z folderu resources.
     * @param fileName nazwa pliku
     * @return odczytana zawartość pliku
     */
    static std::string readTextFile(const std::string &fileName);

private:
    template<typename T>
    static void check(T *pointer, const std::string &fileName) {
        if (pointer == nullptr) {
            throw std::runtime_error("Couldn't open file: " + std::string(fileName));
        }
    }

    static std::string concatenateFilePath(const std::string &fileName);
};


#endif //ZCPP_MISSIONIMPOSSIBLE_FILEMANAGER_H
