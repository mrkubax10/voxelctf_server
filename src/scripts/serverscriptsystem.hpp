#ifndef SRC_SCRIPTS_SERVERSCRIPTSYSTEM_HPP
#define SRC_SCRIPTS_SERVERSCRIPTSYSTEM_HPP
#include "serverscript.hpp"
#include "serverapi.hpp"
#include <map>

class Server;
class ServerScriptSystem{
    std::map<std::string,ServerScript> scripts;
    Server* server;
public:
    ServerScriptSystem(Server* server);
    ServerScript* getServerScript(std::string name);
    static int api_getVersion();
    ServerAPI api;
};
#endif