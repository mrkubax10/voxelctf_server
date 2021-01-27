#ifndef SRC_PLAYERHANDLER_HPP
#define SRC_PLAYERHANDLER_HPP
#include <vector>
#include "connectedplayer.hpp"

enum ServerNetworkCommand{
    MOVE,ACTIVITY,EXIT,READY,CHAT_MESSAGE,WORLD_DATA,REJECT,NEW_PLAYER,CONNECTION
};
class Server;
class PlayerHandler{
    std::vector<ConnectedPlayer> players;
    SDLNet_SocketSet* sockets;
    Server* server;
public:
    PlayerHandler();
    PlayerHandler(SDLNet_SocketSet* sockets,Server* server);
    void update();
    void addPlayer(ConnectedPlayer player);
    void sendNetworkCommandToAllPlayers(char* data,int len);
    void sendNetworkCommandToAllPlayersWithout(char* data,int len,int id);
    ConnectedPlayer getPlayer(int id);
};
#endif