//
// Created by Salach on 21.02.2018.
//

#ifndef ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H
#define ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {
public:
    static const std::string START_GAME;
    static const std::string SETTINGS;
    static const std::string environment_NUMBER;
    static const std::string NUMBER_OF_AGENTS;
    static const std::string RANGE_OF_VIEW;
    static const std::string ANGLE_OF_VIEW;
    static const std::string DEBUG;
    static const std::string ACCEPT;
    static const std::string CANCEL;
    static const std::string QUIT;
    static const std::string YES;
    static const std::string NO;
    static const std::string RESUME_GAME;
    static const std::string RESTART_LEVEL;
    static const std::string MAIN_MENU;

    static std::vector<std::string> splitString(std::string text, char delimiter);

    static void cutString(std::string &text, const std::string &partToBeCut);

    static bool stringStartsWith(const std::string &text, const std::string &part);
};

#endif //ZCPP_MISSIONIMPOSSIBLE_DICTIONARY_H
