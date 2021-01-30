#include <iostream>
#include "server.hpp"
#include <thread>
int main(){
    if(enet_initialize()!=0){
        std::cout<<"(Err) [Server Main] Failed to initalize ENet"<<std::endl;
    }
    Settings settings;
    settings.load("settings.txt");
    std::cout<<"(Log) [Server Main] Server is starting"<<std::endl;
    Server server(&settings);
    server.run();
}