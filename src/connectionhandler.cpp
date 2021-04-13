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
                if(!event->packet)
                    continue;
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
                    ConnectionHandler::server->teamPlayerCount[std::to_string(players[i].getTeam())]--;
                    players.erase(players.begin()+i);
                    server->changePlayerID(-1);
                    server->changePlayerCount(-1);
                }
                else if(data[0]==ServerNetworkCommand::ACTIVITY){
                    players[i].updateActivity();
                    char* sendData=(char*)malloc(1);
                    sendData[0]=ServerNetworkCommand::ACTIVITY;
                    players[i].send(sendData,1);
                    free(sendData);
                }
                else if(data[0]==ServerNetworkCommand::CHAT_MESSAGE){
                    char* sendData=(char*)malloc(data[1]+4);
                    sendData[0]=ServerNetworkCommand::CHAT_MESSAGE;
                    sendData[1]=players[i].getID();
                    sendData[2]=data[1];
                    sendData[3]=data[2];
                    short messageLength;
                    ((uint8_t*)&messageLength)[0]=data[1];
                    ((uint8_t*)&messageLength)[1]=data[2];
                    std::string message="";
                    for(int a=0; a<messageLength; a++){
                        sendData[a+4]=data[3+a];
                        message+=data[3+a];
                    }
                    std::cout<<"(Log) [ConnectionHandler] Player "<<players[i].getName()<<" has written on chat: "<<message<<std::endl;
                    ConnectionHandler::sendNetworkCommandToAllPlayersWithout(sendData,data[1]+4,players[i].getID());
                    
                }
                enet_packet_destroy(event->packet);
            }
        }
    }
}
void ConnectionHandler::addPlayer(ConnectedPlayer player){
    if(ConnectionHandler::players.size()>0){
        char* sendData=(char*)malloc(4+player.getName().length());
        sendData[0]=ServerNetworkCommand::NEW_PLAYER;
        sendData[1]=0;
        sendData[2]=ConnectionHandler::server->getPlayerID()-1;
        sendData[3]=player.getName().length();
        for(int i=0; i<player.getName().length(); i++){
            sendData[4+i]=player.getName()[i];
        }
        ConnectionHandler::sendNetworkCommandToAllPlayers(sendData,4+player.getName().length());
        free(sendData);
    }
    
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
std::vector<ConnectedPlayer>& ConnectionHandler::getPlayerList(){
    return players;
}