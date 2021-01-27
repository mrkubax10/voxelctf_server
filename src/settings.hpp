#ifndef SRC_SETTINGS_HPP
#define SRC_SETTINGS_HPP
#include <iostream>
#include <fstream>
#include "utils.hpp"
class Settings{
public:
    int port;
    int maxplayers;
    std::string mapName;
    Settings();
    void load(std::string f);
};
#endif