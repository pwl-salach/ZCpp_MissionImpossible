//
// Created by salach on 3/1/18.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_FILEMANAGER_H
#define ZCPP_MISSIONIMPOSSIBLE_FILEMANAGER_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include <cstring>

class FileManager {
public:
    static TTF_Font *loadFont(const std::string &fileName, uint8_t size);

    static SDL_Surface *loadImage(const std::string &fileName);

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
