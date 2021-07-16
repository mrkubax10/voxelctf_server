#ifndef SRC_SCRIPTS_SERVERAPI_HPP
#define SRC_SCRIPTS_SERVERAPI_HPP
#include <lua5.1/lua.hpp>
class Server;
class ServerScriptSystem;
class ServerAPI{
    static Server* server;
    static ServerScriptSystem* scriptSystem;
public:
    static void init(Server* server,ServerScriptSystem* system);
    // Misc functions
    static int getVersion(lua_State* L);
    // Player functions
    static int getPlayerCount(lua_State* L);
};
#endif