//
// Created by Salach on 21.02.2018.
//
#include <algorithm>
#include <sstream>
#include <cstring>
#include "Dictionary.h"

const std::string Dictionary::START_GAME = "New Game";
const std::string Dictionary::SETTINGS = "Settings";
const std::string Dictionary::environment_NUMBER = "Environment number";
const std::string Dictionary::NUMBER_OF_AGENTS = "Number of Agent";
const std::string Dictionary::RANGE_OF_VIEW = "Range of view";
const std::string Dictionary::ANGLE_OF_VIEW = "Angle of view";
const std::string Dictionary::DEBUG = "Debug";
const std::string Dictionary::ACCEPT = "Accept";
const std::string Dictionary::CANCEL = "Cancel";
const std::string Dictionary::QUIT = "Quit";
const std::string Dictionary::YES = "Yes";
const std::string Dictionary::NO = "No";
const std::string Dictionary::RESUME_GAME = "Resume Game";
const std::string Dictionary::RESTART_LEVEL = "Restart Level";
const std::string Dictionary::MAIN_MENU = "Main Menu";

std::vector<std::string> Dictionary::splitString(std::string text, char delimiter) {
    std::vector<std::string> ret;
    std::replace(text.begin(), text.end(), delimiter, ' ');
    std::stringstream ss(text);
    std::string temp;
    while (ss >> temp)
        ret.push_back(temp);
    return ret;
}

void Dictionary::cutString(std::string &text, const std::string &partToBeCut) {
    std::string::size_type position = text.find(partToBeCut);
    if (position == std::string::npos) {
        throw std::runtime_error("String: " + text + " doesn't contain :" + partToBeCut);
    }
    text.erase(position, partToBeCut.length());
}

bool Dictionary::stringStartsWith(const std::string &text, const std::string &part) {
    return std::strncmp(text.c_str(), part.c_str(), part.size()) == 0;
}
