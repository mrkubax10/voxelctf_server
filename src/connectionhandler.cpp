#include "connectionhandler.hpp"
#include "server.hpp"
ConnectionHandler::ConnectionHandler(Server* server){
    ConnectionHandler::server=server;
}
ConnectionHandler::ConnectionHandler(){

}
void ConnectionHandler::update(ENetEvent* event){
    if(event->type==ENET_EVENT_TYPE_RECEIVE){
        for(int i=0; i<ConnectionHandler::players.size(); i++){
            if(event->peer==ConnectionHandler::players[i].getSocket()){
                char* data=(char*)event->packet->data;
                if(data[0]==ServerNetworkCommand::MOVE){
                    char* sendData=(char*)malloc(2+3*4);
                    int sendDataLength=2+3*4;
                    sendData[0]=ServerNetworkCommand::MOVE;
                    sendData[1]=(uint8_t)players[i].getID();
                    for(int a=1; a<3*4+1; a++){
                        sendData[a+2]=data[a+1];
                    }
                    ConnectionHandler::sendNetworkCommandToAllPlayersWithout(sendData,sendDataLength,players[i].getID());
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
                    ConnectionHandler::sendNetworkCommandToAllPlayersWithout(sendData,sendDataLength,players[i].getID());
                    std::cout<<"(Log) [Server Main] Player "<<players[i].getName()<<" left the game"<<std::endl;
                    players.erase(players.begin()+i);
                    server->changePlayerID(-1);
                    server->changePlayerCount(-1);
                }
                else if(data[0]==ServerNetworkCommand::ACTIVITY){
                    
                }
                if(event->packet)
                    enet_packet_destroy(event->packet);
            }
        }
    }
}
void ConnectionHandler::addPlayer(ConnectedPlayer player){
    ConnectionHandler::players.push_back(player);
}
void ConnectionHandler::sendNetworkCommandToAllPlayers(char* data,int len){
    for(int i=0; i<ConnectionHandler::players.size(); i++){
        ConnectionHandler::players[i].send(data,len);
    }
}
void ConnectionHandler::sendNetworkCommandToAllPlayersWithout(char* data,int len,int id){
    for(int i=0; i<ConnectionHandler::players.size(); i++){
        if(ConnectionHandler::players[i].getID()!=id){
            ConnectionHandler::players[i].send(data,len);
            std::cout<<"Sending"<<std::endl;
        }
    }
}
ConnectedPlayer ConnectionHandler::getPlayer(int id){
    for(int i=0; i<players.size(); i++){
        if(players[i].getID()==id){
            return players[i];
        }
    }
    return players[0];
}