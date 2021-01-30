#include "connectedplayer.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,ENetPeer* peer,int id){
    ConnectedPlayer::name=name;
    ConnectedPlayer::id=id;
    ConnectedPlayer::socket=peer;
}
void ConnectedPlayer::send(char* data,int len){
    ENetPacket* packet=enet_packet_create(data,len,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(ConnectedPlayer::socket,0,packet);
    enet_packet_destroy(packet);
}
char* ConnectedPlayer::recv(){
    char* data=(char*)malloc(MAX_MESSAGE_LENGTH);
    
    return data;
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
ENetPeer* ConnectedPlayer::getSocket(){
    return socket;
}