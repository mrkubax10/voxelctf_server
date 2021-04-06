#ifndef SRC_SERVER_HPP
#define SRC_SERVER_HPP
#include <asio.hpp>
#include <iostream>
#include "settings.hpp"
#include "connectionhandler.hpp"
#include "commandinterpreter.hpp"
#include <thread>
#include "scripts/serverscriptsystem.hpp"
extern char* SERVER_VERSION;
class Server{
    int port;
    bool running;
    Settings* settings;
    ConnectionHandler connectionHandler;
    std::vector<char> mapData;
    int playerCount;
    int playerID;
    CommandInterpreter commandInterpreter;
    ENetHost* host;
    ENetAddress address;
    ENetEvent event;
    bool playerWaiting;
    ServerScriptSystem scriptSystem;
public:
    Server();
    Server(Settings* settings);
    void run();
    bool isRunning();
    void setRunning(bool running);
    void loadMapData();
    void sendPlayerDataToPlayer(ConnectedPlayer* player);
    void sendWorldDataToPlayer(ConnectedPlayer* player);
    void changePlayerID(int i);
    void changePlayerCount(int i);
    int getPlayerID();
    ENetHost* getHost();
};
#endif