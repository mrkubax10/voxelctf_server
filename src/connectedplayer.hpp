#ifndef SRC_CONNECTEDPLAYER_HPP
#define SRC_CONNECTEDPLAYER_HPP
#include <iostream>
#include <enet/enet.h>
#define MAX_MESSAGE_LENGTH 65537 // sizeof(unsigned short)+2
class ConnectedPlayer{
    std::string name;
    int id;
    long lastActivity;
    float x,y,z;
    ENetPeer* socket;
public:
    ConnectedPlayer(std::string name,ENetPeer* socket,int id);
    void send(char* data,int len);
    char* recv();
    std::string getName();
    ENetPeer* getSocket();
    int getID();
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
};
#endif