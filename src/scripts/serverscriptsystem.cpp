#include "serverscriptsystem.hpp"
#include "../server.hpp"
ServerScriptSystem::ServerScriptSystem(Server* server):api(server,this){
    ServerScriptSystem::server=server;
}
ServerScript* ServerScriptSystem::getServerScript(std::string name){
    return &scripts[name];
}