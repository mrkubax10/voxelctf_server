#include "serverscriptsystem.hpp"
#include "../server.hpp"
ServerScriptSystem::ServerScriptSystem(Server* server){
    ServerScriptSystem::server=server;
    ServerAPI::init(server,this);
}
ServerScript* ServerScriptSystem::getServerScript(std::string name){
    if(!scripts.count(name))
        scripts[name]=ServerScript(name,this);
    return &scripts[name];
}