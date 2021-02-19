#ifndef SRC_SCRIPTS_SERVERAPI_HPP
#define SRC_SCRIPTS_SERVERAPI_HPP
#include <lua5.1/lua.hpp>
class Server;
class ServerScriptSystem;
class ServerAPI{
    Server* server;
    ServerScriptSystem* scriptSystem;
public:
    ServerAPI(Server* server,ServerScriptSystem* system);

    int getVersion(lua_State* L);

};
#endif