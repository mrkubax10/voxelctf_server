#include "server.hpp"
Server::Server(Settings* settings):scriptSystem(this){
    Server::port=settings->port;
    Server::address.host=ENET_HOST_ANY;
    Server::address.port=Server::port;
    Server::host=enet_host_create(&address,10,2,0,0);
    Server::settings=settings;
    Server::running=true;
    Server::connectionHandler=ConnectionHandler(this);
    Server::playerCount=0;
    Server::playerID=0;
    Server::commandInterpreter=CommandInterpreter(this);
    Server::loadMapData();
    Server::playerWaiting=false;
    // std::thread commandInterpreterThread([&](){
    //     while(commandInterpreter.input!="exit"){
    //         std::cout<<">";
    //         getline(std::cin,commandInterpreter.input);
    //     }
    // });
}
void Server::run(){
    
    while(Server::running){
        while(enet_host_service(Server::host,&event,0)){
            if(event.type==ENET_EVENT_TYPE_CONNECT){
                Server::playerWaiting=true;
                
            }
            else if(event.type==ENET_EVENT_TYPE_RECEIVE && Server::playerWaiting){
                if(event.packet->data[0]==ServerInitializationCommand::INITIALIZE){
                    int nameLength=event.packet->data[1];
                    std::string name;
                    for(int i=0; i<nameLength; i++){
                        name+=event.packet->data[i+2];
                    }
                    ConnectedPlayer player(name,this,event.peer,Server::playerID++);
                    std::cout<<"(Log) [Server] Player "<<name<<" joined the game with ID "<<Server::playerID-1<<std::endl;
                    Server::sendPlayerDataToPlayer(&player);
                    Server::sendWorldDataToPlayer(&player);
                    connectionHandler.addPlayer(player);
                    Server::playerWaiting=false;
                }
            }
            else
                Server::connectionHandler.update(&event);
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
    std::cout<<"(Log) [Server] Loading map "<<Server::settings->mapName<<std::endl;
    std::ifstream file("res/maps/"+Server::settings->mapName+".voxelctf",std::ios::in|std::ios::binary);
    if(!file.good()){
        std::cout<<"(Err) [Server] Failed to load map "<<std::endl;
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
    char* sendData=(char*)malloc(1+mapData.size());
    int sendDataLength=1+mapData.size();
    sendData[0]=ServerInitializationCommand::MAP_DATA;
    for(int i=0; i<mapData.size(); i++){
        sendData[i+1]=mapData[i];
    }
    player->send(sendData,sendDataLength);
    free(sendData);
}

ENetHost* Server::getHost(){
    return host;
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