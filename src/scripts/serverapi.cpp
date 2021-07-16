#include "serverapi.hpp"
#include "../server.hpp"
#include "serverscriptsystem.hpp"
Server* ServerAPI::server;
ServerScriptSystem* ServerAPI::scriptSystem;
void ServerAPI::init(Server* server,ServerScriptSystem* system){
    ServerAPI::server=server;
    ServerAPI::scriptSystem=system;
}
int ServerAPI::getVersion(lua_State* state){
    int argumentCount=lua_gettop(state);
    if(argumentCount!=0){
        std::cout<<"(ServerScript Err) [ServerScript] server_getVersion expects 0 arguments"<<std::endl;
        return 0;
    }
    lua_pushstring(state,"dev");
    return 1;
}
int ServerAPI::getPlayerCount(lua_State* state){
    int argumentCount=lua_gettop(state);
    if(argumentCount!=0){
        std::cout<<"(ServerScript Err) [ServerScript] server_getPlayerCount expects 0 arguments"<<std::endl;
        return 0;
    }
    lua_pushinteger(state,ServerAPI::server->getPlayerID());
    return 1;
}