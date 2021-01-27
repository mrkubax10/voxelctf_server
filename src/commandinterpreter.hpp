#ifndef SRC_COMMANDINTERPRETER_HPP
#define SRC_COMMANDINTERPRETER_HPP
#include <iostream>
#include "utils.hpp"
class Server;
class CommandInterpreter{
    std::string input;
    Server* server;
public:
    CommandInterpreter();
    CommandInterpreter(Server* server);
    void processInput();
    void interprete(std::string line);
};
#endif