#ifndef SRC_CONNECTEDPLAYER_HPP
#define SRC_CONNECTEDPLAYER_HPP
#include <iostream>
#include <enet/enet.h>
#define MAX_MESSAGE_LENGTH 65537 // sizeof(unsigned short)+2

class Server;
class ConnectedPlayer{
    std::string name;
    int id;
    long lastActivity;
    float x,y,z;
    ENetPeer* socket;
    Server* server;
    uint8_t team;
public:
    ConnectedPlayer(std::string name,Server* server,ENetPeer* socket,int id,uint8_t team);
    void send(char* data,int len);
    ENetPacket* recv();
    std::string getName();
    ENetPeer* getSocket();
    int getID();
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setTeam(uint8_t team);
    uint8_t getTeam();
};
#endif