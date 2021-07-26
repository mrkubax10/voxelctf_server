#include "scripts/serverapi.hpp"
#include "server.hpp"
#include "scripts/serverscriptsystem.hpp"
#include "whitelist.hpp"
Server* ServerAPI::server;
ServerScriptSystem* ServerAPI::scriptSystem;
std::string ServerAPI::scriptName="";
void ServerAPI::init(Server* server,ServerScriptSystem* system){
    ServerAPI::server=server;
    ServerAPI::scriptSystem=system;
}
void ServerAPI::setScriptName(std::string name){
    ServerAPI::scriptName=name;
}
bool ServerAPI::checkArgumentCount(int argumentCount,int count,std::string functionName){
    if(argumentCount!=count){
        std::cout<<"(ServerScript Err) [ServerScript] "<<ServerAPI::scriptName<<": "<<functionName<<" expects "<<count<<" "<<(count==1?"argument":"arguments")<<std::endl;
        return false;
    }
    return true;
}
int ServerAPI::getVersion(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),0,"server_getVersion")){
        lua_error(state);
        return 0;
    }
    lua_pushstring(state,"dev");
    return 1;
}
int ServerAPI::print(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"print")){
        lua_error(state);
        return 0;
    }
    std::cout<<"(ServerScript Log) [ServerScript] "<<ServerAPI::scriptName<<": "<<lua_tostring(state,1)<<std::endl;
    return 0;
}
int ServerAPI::getPlayerCount(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),0,"server_getPlayerCount")){
        lua_error(state);
        return 0;
    }
    lua_pushinteger(state,ServerAPI::server->getPlayerID());
    return 1;
}
int ServerAPI::getResource(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"server_getResource")){
        lua_error(state);
        return 0;
    }
    std::string resource=lua_tostring(state,1);
    lua_pushstring(state,std::string("res/server/scripts/"+ServerAPI::scriptName+"/"+resource).c_str());
    return 1;
}
int ServerAPI::registerBlock(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),2,"server_registerBlock")){
        lua_error(state);
        return 0;
    }
    return 0;
}
int ServerAPI::isWhitelistEnabled(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),0,"server_isWhitelistEnabled")){
        lua_error(state);
        return 0;
    }
    lua_pushboolean(state,ServerAPI::server->getWhitelist().isEnabled());
    return 1;
}
int ServerAPI::setWhitelistEnabled(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"server_setWhitelistEnabled")){
        lua_error(state);
        return 0;
    }
    bool enabled=lua_toboolean(state,1);
    ServerAPI::server->getWhitelist().setEnabled(enabled);
    return 0;
}
int ServerAPI::isPlayerInWhitelist(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"server_isPlayerInWhitelist")){
        lua_error(state);
        return 0;
    }
    std::string player=lua_tostring(state,1);
    lua_pushboolean(state,ServerAPI::server->getWhitelist().isInWhitelist(player));
    return 1;
}
int ServerAPI::addPlayerToWhitelist(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"server_addPlayerToWhitelist")){
        lua_error(state);
        return 0;
    }
    std::string player=lua_tostring(state,1);
    ServerAPI::server->getWhitelist().addToWhitelist(player);
    return 0;
}
int ServerAPI::removePlayerFromWhitelist(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),1,"server_removePlayerFromWhitelist")){
        lua_error(state);
        return 0;
    }
    std::string player=lua_tostring(state,1);
    ServerAPI::server->getWhitelist().removeFromWhitelist(player);
    return 0;
}
int ServerAPI::getWhitelistContent(lua_State* state){
    if(!ServerAPI::checkArgumentCount(lua_gettop(state),0,"server_getWhitelistContent")){
        lua_error(state);
        return 0;
    }
    lua_createtable(state,0,ServerAPI::server->getWhitelist().getContent().size());
    for(int i=0; i<ServerAPI::server->getWhitelist().getContent().size(); i++){
        lua_pushinteger(state,i);
        lua_pushstring(state,ServerAPI::server->getWhitelist().getContent()[i].c_str());
        lua_settable(state,-3);
    }
    return 1;
}