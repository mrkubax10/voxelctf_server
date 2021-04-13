#include "connectedplayer.hpp"
#include "server.hpp"
ConnectedPlayer::ConnectedPlayer(std::string name,Server* server,ENetPeer* peer,int id,uint8_t team){
    ConnectedPlayer::name=name;
    ConnectedPlayer::id=id;
    ConnectedPlayer::socket=peer;
    ConnectedPlayer::server=server;
    ConnectedPlayer::team=team;
}
void ConnectedPlayer::send(char* data,int len){
    ENetPacket* packet=enet_packet_create(data,len,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(ConnectedPlayer::socket,0,packet);
    enet_host_flush(server->getHost());
}
void ConnectedPlayer::setTeam(uint8_t team){
    ConnectedPlayer::team=team;
}
uint8_t ConnectedPlayer::getTeam(){
    return ConnectedPlayer::team;
}
void ConnectedPlayer::updateActivity(){
    ConnectedPlayer::lastActivity=time(0);
}
long ConnectedPlayer::getLastActivity(){
    return lastActivity;
}
ENetPacket* ConnectedPlayer::recv(){
    ENetPacket* packet=enet_peer_receive(ConnectedPlayer::socket,0);
    return packet;
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