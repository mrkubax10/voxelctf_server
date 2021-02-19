#include "commandinterpreter.hpp"
#include "server.hpp"
CommandInterpreter::CommandInterpreter(){
    
}
CommandInterpreter::CommandInterpreter(Server* server){
    CommandInterpreter::server=server;
}
void CommandInterpreter::interprete(std::string line){
    std::vector<std::string> params=split(line,' ');
    if(params[0]=="exit"){
        CommandInterpreter::server->setRunning(false);
    }
}