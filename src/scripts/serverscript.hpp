#ifndef SRC_SCRIPTS_SERVERSCRIPT_HPP
#define SRC_SCRIPTS_SERVERSCRIPT_HPP
#include <lua5.1/lua.hpp>
#include <iostream>
class ServerScriptSystem;
class ServerScript{
    lua_State* state;
    std::string name;
    bool exited;
    ServerScriptSystem* scriptSystem;
public:
    ServerScript(std::string name,ServerScriptSystem* scriptSystem);
    ServerScript();
    void run();
    void throwError(std::string inf);
};
#endif