#include "connectedplayer.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,TCPsocket socket,int id){
    ConnectedPlayer::name=name;
    ConnectedPlayer::socket=socket;
    ConnectedPlayer::id=id;
}
void ConnectedPlayer::send(char* data,int len){
    SDLNet_TCP_Send(ConnectedPlayer::socket,data,len);
}
char* ConnectedPlayer::recv(){
    char* data=(char*)malloc(MAX_MESSAGE_LENGTH);
    SDLNet_TCP_Recv(ConnectedPlayer::socket,data,MAX_MESSAGE_LENGTH);
    return data;
}
TCPsocket ConnectedPlayer::getSocket(){
    return ConnectedPlayer::socket;
}
std::string ConnectedPlayer::getName(){
    return ConnectedPlayer::name;
}
int ConnectedPlayer::getID(){
    return ConnectedPlayer::id;
}
float ConnectedPlayer::getX(){
    return x;
}
float ConnectedPlayer::getY(){
    return y;
}
float ConnectedPlayer::getZ(){
    return z;
}
void ConnectedPlayer::setX(float x){
    ConnectedPlayer::x=x;
}
void ConnectedPlayer::setY(float y){
    ConnectedPlayer::y=y;
}
void ConnectedPlayer::setZ(float z){
    ConnectedPlayer::z=z;
}