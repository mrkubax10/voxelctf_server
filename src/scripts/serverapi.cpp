#include "serverapi.hpp"
#include "../server.hpp"
#include "serverscriptsystem.hpp"

ServerAPI::ServerAPI(Server* server,ServerScriptSystem* scriptSystem){
    ServerAPI::server=server;
    ServerAPI::scriptSystem=scriptSystem;
}
int ServerAPI::getVersion(lua_State* L){
    int argumentCount=lua_gettop(L);
    if(argumentCount!=0){
        std::cout<<"ServerScript error"<<std::endl;
        return 0;
    }
    lua_pushstring(L,"dev");
    return 1;
}