#ifndef SRC_SCRIPTS_SERVERAPI_HPP
#define SRC_SCRIPTS_SERVERAPI_HPP
#include <lua5.1/lua.hpp>
#include <string>
class Server;
class ServerScriptSystem;
class ServerAPI{
    static Server* server;
    static ServerScriptSystem* scriptSystem;
    static std::string scriptName;
public:
    static void init(Server* server,ServerScriptSystem* system);
    static void setScriptName(std::string name);
    static bool checkArgumentCount(int argumentCount,int count,std::string functionName);
    // Misc functions
    static int getVersion(lua_State* state);
    static int print(lua_State* state);
    // Player functions
    static int getPlayerCount(lua_State* state);
    // Filesystem functions
    static int getResource(lua_State* state);
    // Block functions
    static int registerBlock(lua_State* state);
    // Whitelist functions
    static int isWhitelistEnabled(lua_State* state);
    static int setWhitelistEnabled(lua_State* state);
    static int isPlayerInWhitelist(lua_State* state);
    static int addPlayerToWhitelist(lua_State* state);
    static int removePlayerFromWhitelist(lua_State* state);
    static int getWhitelistContent(lua_State* state);
};
#endif