#include "server.hpp"
Server::Server(Settings* settings){
    Server::port=settings->port;
    Server::address.host=ENET_HOST_ANY;
    Server::address.port=Server::port;
    Server::host=enet_host_create(&address,settings->maxplayers,2,0,0);
    Server::settings=settings;
    Server::running=true;
    Server::connectionHandler=ConnectionHandler(this);
    Server::playerCount=0;
    Server::playerID=0;
    Server::commandInterpreter=CommandInterpreter(this);
    Server::loadMapData();
    Server::playerWaiting=false;
    //std::thread commandInterpreterThread([&](){
    //    commandInterpreter.processInput();
    //});
}
void Server::run(){
    while(Server::running){
        while(enet_host_service(Server::host,&event,50)){
            if(event.type==ENET_EVENT_TYPE_CONNECT){
                Server::playerWaiting=true;
            }
            else if(event.type==ENET_EVENT_TYPE_RECEIVE && Server::playerWaiting){
                if(event.packet->data[0]==ServerInitializationCommand::INITIALIZE){
                    char* playerName=(char*)malloc(event.packet->data[1]+1);
                    for(int i=0; i<event.packet->data[1]; i++){
                        playerName[i]=event.packet->data[i+2];
                    }
                    playerName[event.packet->data[1]]='\0';
                    ConnectedPlayer player(playerName,event.peer,Server::playerID++);
                    Server::connectionHandler.addPlayer(player);
                    enet_packet_destroy(event.packet);
                    Server::sendPlayerDataToPlayer(&player);
                    Server::sendWorldDataToPlayer(&player);
                }
                Server::playerWaiting=false;
            }
            else{
                Server::connectionHandler.update(Server::event);
            }
        }
    }
}
bool Server::isRunning(){
    return Server::running;
}
void Server::setRunning(bool running){
    Server::running=running;
}
void Server::loadMapData(){
    std::cout<<"(Log) [Server Main] Loading map "<<Server::settings->mapName<<std::endl;
    std::ifstream file("res/maps/"+Server::settings->mapName+".voxelctf",std::ios::in|std::ios::binary);
    if(!file.good()){
        std::cout<<"(Err) [Server Main] Failed to load map "<<std::endl;
        Server::running=false;
    }
    char byte;
    while(!file.eof()){
        file.read(&byte,1);
        mapData.push_back(byte);
    }
    file.close();
}
void Server::sendPlayerDataToPlayer(ConnectedPlayer* player){
    std::vector<char> sendData;
    sendData.push_back(ServerInitializationCommand::PLAYER_DATA);
    sendData.push_back(Server::playerCount);
    for(int i=0; i<Server::playerCount; i++){
        sendData.push_back(i);
        sendData.push_back(Server::connectionHandler.getPlayer(i).getName().length());
        for(int b=0; b<Server::connectionHandler.getPlayer(i).getName().length(); b++){
            sendData.push_back(Server::connectionHandler.getPlayer(i).getName()[b]);
        }
        float x=Server::connectionHandler.getPlayer(i).getX();
        float y=Server::connectionHandler.getPlayer(i).getY();
        float z=Server::connectionHandler.getPlayer(i).getZ();
        sendData.push_back(((uint8_t*)&x)[0]);
        sendData.push_back(((uint8_t*)&x)[1]);
        sendData.push_back(((uint8_t*)&x)[2]);
        sendData.push_back(((uint8_t*)&x)[3]);
        sendData.push_back(((uint8_t*)&y)[0]);
        sendData.push_back(((uint8_t*)&y)[1]);
        sendData.push_back(((uint8_t*)&y)[2]);
        sendData.push_back(((uint8_t*)&y)[3]);
        sendData.push_back(((uint8_t*)&z)[0]);
        sendData.push_back(((uint8_t*)&z)[1]);
        sendData.push_back(((uint8_t*)&z)[2]);
        sendData.push_back(((uint8_t*)&z)[3]);
    }
    player->send(sendData.data(),sendData.size());
}
void Server::sendWorldDataToPlayer(ConnectedPlayer* player){
    char* sendData=(char*)malloc(7+mapData.size());
    int sendDataLength=7+mapData.size();
    sendData[0]=ServerInitializationCommand::MAP_DATA;
    unsigned short mapDataSize=mapData.size();
    sendData[1]=((uint8_t*)&mapDataSize)[0];
    sendData[2]=((uint8_t*)&mapDataSize)[1];
    for(int i=0; i<mapData.size(); i++){
        sendData[3+i]=mapData[i];
    }
    for(int i=0; i<5; i++){
        sendData[mapData.size()+i]=255;
    }
    player->send(sendData,sendDataLength);
    free(sendData);
}
void Server::changePlayerID(int i){
    Server::playerID+=i;
}
int Server::getPlayerID(){
    return Server::playerID;
}
void Server::changePlayerCount(int i){
    Server::playerCount+=i;
}