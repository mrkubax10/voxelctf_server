#include "playerhandler.hpp"
#include "server.hpp"
PlayerHandler::PlayerHandler(SDLNet_SocketSet* sockets,Server* server){
    PlayerHandler::sockets=sockets;
    PlayerHandler::server=server;
}
PlayerHandler::PlayerHandler(){

}
void PlayerHandler::update(){
    if(SDLNet_CheckSockets(*sockets,200)){
        for(int i=0; i<PlayerHandler::players.size(); i++){
            if(SDLNet_SocketReady(PlayerHandler::players[i].getSocket())){
                char* data=PlayerHandler::players[i].recv();
                if(data[0]==ServerNetworkCommand::READY){
                    std::cout<<"READY"<<std::endl;
                    char* sendData=(char*)malloc(2+1+players[i].getName().length());
                    int sendDataLength=2+1+players[i].getName().length();
                    sendData[0]=ServerNetworkCommand::NEW_PLAYER;
                    sendData[1]=(uint8_t)players[i].getID();
                    sendData[2]=players[i].getName().length();
                    for(int a=0; a<players[i].getName().length(); a++){
                        sendData[a+3]=players[i].getName()[a];
                    }
                    PlayerHandler::sendNetworkCommandToAllPlayersWithout(sendData,sendDataLength,players[i].getID());
                    free(sendData);
                }
                else if(data[0]==ServerNetworkCommand::MOVE){
                    char* sendData=(char*)malloc(2+3*4);
                    int sendDataLength=2+3*4;
                    sendData[0]=ServerNetworkCommand::MOVE;
                    sendData[1]=(uint8_t)players[i].getID();
                    for(int a=1; a<3*4+1; a++){
                        sendData[a+2]=data[a+1];
                    }
                    PlayerHandler::sendNetworkCommandToAllPlayersWithout(sendData,sendDataLength,players[i].getID());
                    float x,y,z;
                    ((uint8_t*)&x)[0]=data[1];
                    ((uint8_t*)&x)[1]=data[2];
                    ((uint8_t*)&x)[2]=data[3];
                    ((uint8_t*)&x)[3]=data[4];
                    ((uint8_t*)&y)[0]=data[5];
                    ((uint8_t*)&y)[1]=data[6];
                    ((uint8_t*)&y)[2]=data[7];
                    ((uint8_t*)&y)[3]=data[8];
                    ((uint8_t*)&z)[0]=data[9];
                    ((uint8_t*)&z)[1]=data[10];
                    ((uint8_t*)&z)[2]=data[11];
                    ((uint8_t*)&z)[3]=data[12];
                    players[i].setX(x);
                    players[i].setY(y);
                    players[i].setZ(z);
                    free(sendData);
                }
                else if(data[0]==ServerNetworkCommand::EXIT){
                    char* sendData=(char*)malloc(2);
                    int sendDataLength=2;
                    sendData[0]=ServerNetworkCommand::EXIT;
                    sendData[1]=players[i].getID();
                    PlayerHandler::sendNetworkCommandToAllPlayersWithout(sendData,sendDataLength,players[i].getID());
                    std::cout<<"(Log) [Server Main] Player "<<players[i].getName()<<" left the game"<<std::endl;
                    players.erase(players.begin()+i);
                    server->changePlayerID(-1);
                    server->changePlayerCount(-1);
                    std::cout<<server->getPlayerID()<<std::endl;
                }
                else if(data[0]==ServerNetworkCommand::ACTIVITY){
                    
                }
                free(data);
            }
        }
    }
}
void PlayerHandler::addPlayer(ConnectedPlayer player){
    PlayerHandler::players.push_back(player);
}
void PlayerHandler::sendNetworkCommandToAllPlayers(char* data,int len){
    for(int i=0; i<PlayerHandler::players.size(); i++){
        PlayerHandler::players[i].send(data,len);
    }
}
void PlayerHandler::sendNetworkCommandToAllPlayersWithout(char* data,int len,int id){
    for(int i=0; i<PlayerHandler::players.size(); i++){
        if(PlayerHandler::players[i].getID()!=id){
            PlayerHandler::players[i].send(data,len);
            std::cout<<"Sending"<<std::endl;
        }
    }
}
ConnectedPlayer PlayerHandler::getPlayer(int id){
    for(int i=0; i<players.size(); i++){
        if(players[i].getID()==id){
            return players[i];
        }
    }
    return players[0];
}