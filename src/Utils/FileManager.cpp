//
// Created by salach on 3/1/18.
//

#include <SDL2/SDL_image.h>
#include <fstream>
#include "FileManager.h"


TTF_Font *FileManager::loadFont(const std::string &fileName, uint8_t size) {
    if (!TTF_WasInit()){
        TTF_Init();
    }
    std::string filePath = FileManager::concatenateFilePath(fileName);
    TTF_Font *ret = TTF_OpenFont(filePath.c_str(), size);
    check<TTF_Font>(ret, fileName);
    return ret;
}

SDL_Surface *FileManager::loadImage(const std::string &fileName) {
    std::string filePath = FileManager::concatenateFilePath(fileName);
    SDL_Surface *ret = IMG_Load(filePath.c_str());
    check<SDL_Surface>(ret, fileName);
    return ret;
}

std::string FileManager::readTextFile(const std::string &fileName) {
    std::string ret, line;
    std::string filePath = FileManager::concatenateFilePath(fileName);
    std::ifstream file(filePath);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            ret += line + "\n";
        }
        file.close();
    }
    return ret;
}
