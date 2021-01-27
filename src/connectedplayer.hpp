#ifndef SRC_CONNECTEDPLAYER_HPP
#define SRC_CONNECTEDPLAYER_HPP
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#define MAX_MESSAGE_LENGTH 65537 // sizeof(unsigned short)+2
class ConnectedPlayer{
    std::string name;
    TCPsocket socket;
    int id;
    long lastActivity;
    float x,y,z;
public:
    ConnectedPlayer(std::string name,TCPsocket socket,int id);
    void send(char* data,int len);
    char* recv();
    TCPsocket getSocket();
    std::string getName();
    int getID();
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
};
#endif