#include "server.hpp"
Server::Server(Settings* settings){
    Server::port=settings->port;
    Server::settings=settings;
    SDLNet_ResolveHost(&address,0,Server::port);
    Server::socket=SDLNet_TCP_Open(&address);
    if(!Server::socket){
        std::cout<<"(Err) [Server] Can't open server socket: "<<SDLNet_GetError()<<std::endl;
        return;
    }
    Server::running=true;
    Server::sockets=SDLNet_AllocSocketSet(settings->maxplayers);
    Server::playerHandler=PlayerHandler(&sockets,this);
    Server::playerCount=0;
    Server::currentPlayerID=0;
    Server::commandInterpreter=CommandInterpreter(this);
    Server::loadMapData();
    
    // std::thread commandInterpreterThread([commandInterpreter](){
    //     commandInterpreter.processInput();
    // });
}
void Server::run(){
    while(Server::running){
        
        TCPsocket player=SDLNet_TCP_Accept(Server::socket);
        if(player){
            char* data=(char*)malloc(MAX_MESSAGE_LENGTH);
            SDLNet_TCP_Recv(player,data,MAX_MESSAGE_LENGTH);
            if(data[0]==ServerNetworkCommand::CONNECTION){
                char* playerName=(char*)malloc(data[1]+1);
                for(int b=2; b<data[1]+2; b++){
                    playerName[b-2]=data[b];
                }
                playerName[data[1]]='\0';
                if(Server::playerCount+1>Server::settings->maxplayers){
                    std::cout<<"(Log) [Server Main] Rejected player "<<playerName<<" Reason: Server overload"<<std::endl;
                    char* sendData=(char*)malloc(2);
                    sendData[0]=ServerNetworkCommand::REJECT;
                    sendData[1]=0;
                    SDLNet_TCP_Send(player,sendData,2);
                    free(sendData);
                }else{
                    ConnectedPlayer connectedPlayer(playerName,player,Server::currentPlayerID);
                    std::cout<<"(Log) [Server Main] Player "<<playerName<<" joined the game with ID: "<<Server::currentPlayerID<<std::endl;
                    Server::currentPlayerID++;
                    Server::sendPlayerDataToPlayer(&connectedPlayer);
                    Server::sendWorldDataToPlayer(&connectedPlayer);
                    Server::playerHandler.addPlayer(connectedPlayer);
                    SDLNet_TCP_AddSocket(Server::sockets,player);
                    Server::playerCount++;
                }
                
                free(playerName);
            }
            free(data);
        }
        playerHandler.update();
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
    sendData.push_back(1);
    sendData.push_back(Server::playerCount);
    for(int i=0; i<Server::playerCount; i++){
        sendData.push_back(i);
        sendData.push_back(Server::playerHandler.getPlayer(i).getName().length());
        for(int b=0; b<Server::playerHandler.getPlayer(i).getName().length(); b++){
            sendData.push_back(Server::playerHandler.getPlayer(i).getName()[b]);
        }
        float x=Server::playerHandler.getPlayer(i).getX();
        float y=Server::playerHandler.getPlayer(i).getY();
        float z=Server::playerHandler.getPlayer(i).getZ();
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
    char* sendData=(char*)malloc(3+mapData.size());
    int sendDataLength=3+mapData.size();
    sendData[0]=0;
    unsigned short mapDataSize=mapData.size();
    sendData[1]=((uint8_t*)&mapDataSize)[0];
    sendData[2]=((uint8_t*)&mapDataSize)[1];
    for(int i=0; i<mapData.size(); i++){
        sendData[3+i]=mapData[i];
    }
    
    player->send(sendData,sendDataLength);
    free(sendData);
}
void Server::changePlayerID(int i){
    Server::currentPlayerID+=i;
}
int Server::getPlayerID(){
    return Server::currentPlayerID;
}
void Server::changePlayerCount(int i){
    Server::playerCount+=i;
}