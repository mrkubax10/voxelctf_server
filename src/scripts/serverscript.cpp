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
    lua_register(state,"server_getVersion",ServerAPI::getVersion);
    lua_register(state,"server_getPlayerCount",ServerAPI::getPlayerCount);
    luaL_dofile(state,std::string("res/server/scripts/"+ServerScript::name+"/main.lua").c_str());
}
void ServerScript::throwError(std::string info){
    std::cout<<"(Warn) [ServerScript] "<<ServerScript::name<<": "<<info<<std::endl;
    ServerScript::exited=true;
}