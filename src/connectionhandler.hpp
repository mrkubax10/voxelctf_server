#ifndef SRC_CONNECTIONHANDLER_HPP
#define SRC_CONNECTIONHANDLER_HPP
#include <vector>
#include "connectedplayer.hpp"
enum ServerInitializationCommand{

    INITIALIZE,PLAYER_DATA,MAP_DATA,PLAYER_INIT,STATUS,STATUS_RESPONSE
};
enum ServerNetworkCommand{
    MOVE,ACTIVITY,EXIT,READY,CHAT_MESSAGE,WORLD_DATA,REJECT,NEW_PLAYER,CONNECTION
};
class Server;
class ConnectionHandler{
    std::vector<ConnectedPlayer> players;
    Server* server;
public:
    ConnectionHandler();
    ConnectionHandler(Server* server);
    void update(ENetEvent* event);
    void addPlayer(ConnectedPlayer player);
    void sendNetworkCommandToAllPlayers(char* data,int len);
    void sendNetworkCommandToAllPlayersWithout(char* data,int len,int id);
    ConnectedPlayer getPlayer(int id);
};
#endif