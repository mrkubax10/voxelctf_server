#include "serverscript.hpp"
#include "serverscriptsystem.hpp"
ServerScript::ServerScript(){}
ServerScript::ServerScript(std::string name,ServerScriptSystem* scriptSystem){
    ServerScript::name=name;
    
    ServerScript::scriptSystem=scriptSystem;
    ServerScript::state=lua_open();
    luaL_openlibs(state);
    ServerScript::exited=false;
}
void ServerScript::run(){
    ServerAPI::setScriptName(ServerScript::name);
    lua_register(state,"server_getVersion",ServerAPI::getVersion);
    lua_register(state,"print",ServerAPI::print);
    lua_register(state,"server_getPlayerCount",ServerAPI::getPlayerCount);
    lua_register(state,"server_getResource",ServerAPI::getResource);
    lua_register(state,"server_isWhitelistEnabled",ServerAPI::isWhitelistEnabled);
    lua_register(state,"server_setWhitelistEnabled",ServerAPI::setWhitelistEnabled);
    lua_register(state,"server_isPlayerInWhitelist",ServerAPI::isPlayerInWhitelist);
    lua_register(state,"server_addPlayerToWhitelist",ServerAPI::addPlayerToWhitelist);
    lua_register(state,"server_removePlayerFromWhitelist",ServerAPI::removePlayerFromWhitelist);
    lua_register(state,"server_getWhitelistContent",ServerAPI::getWhitelistContent);
    if(luaL_dofile(state,std::string("res/server/scripts/"+ServerScript::name+"/main.lua").c_str())!=0){
        std::cout<<"(ServerScript Err) [ServerScript] "<<ServerScript::name<<": "<<lua_tostring(ServerScript::state,-1)<<std::endl;
    }

}
void ServerScript::throwError(std::string info){
    std::cout<<"(Warn) [ServerScript] "<<ServerScript::name<<": "<<info<<std::endl;
    ServerScript::exited=true;
}