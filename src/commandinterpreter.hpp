#ifndef SRC_COMMANDINTERPRETER_HPP
#define SRC_COMMANDINTERPRETER_HPP
#include <iostream>
#include "utils.hpp"
class Server;
class CommandInterpreter{
    Server* server;
public:
    CommandInterpreter();
    CommandInterpreter(Server* server);
    void interprete(std::string line);
    std::string input;
};
#endif