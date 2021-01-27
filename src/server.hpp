#ifndef SRC_SERVER_HPP
#define SRC_SERVER_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <iostream>
#include "settings.hpp"
#include "playerhandler.hpp"
#include "commandinterpreter.hpp"
#include <thread>
class Server{
    TCPsocket socket;
    IPaddress address;
    int port;
    bool running;
    Settings* settings;
    PlayerHandler playerHandler;
    SDLNet_SocketSet sockets;
    std::vector<char> mapData;
    int playerCount;
    int currentPlayerID;
    CommandInterpreter commandInterpreter;
public:
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
};
#endif