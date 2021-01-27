#include <iostream>
#include "server.hpp"
#include <thread>
int main(){
    SDL_Init(SDL_INIT_TIMER);
    SDLNet_Init();
    Settings settings;
    settings.load("settings.txt");
    std::cout<<"(Log) [Server Main] Server is starting"<<std::endl;
    Server server(&settings);
    server.run();
}